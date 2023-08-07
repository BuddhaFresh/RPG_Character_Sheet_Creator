#include "../../menus.h"
#include "../../diceroller.h"
#include "BRP.h"




//GOAL FOR SCRIPT
//everything needed to make a standard Basic Role-Playing Character (5th ed, Universal Game Engine)
//Needs to have attrabutes, diraived stats, list of relivent features, equipment(just a basic set for now)
//class BRP char with roll inputs


//Classes
Dice PLAY;


//Create folder for character sheets
void FolderOriginBRP()
{
  std::string foldername = "Characters/BRP";
  int result = mkdir(foldername.c_str(), 0777); //0777 is premissions for the folder, 7 is full permission and the three number posistions at the end are for different kinds of users? 
  if (result == 0) 
  {
    std::cout << "BRP Installed\n";
  }
  else {  }
}

//Special Dice Rolls for this system
//Rolls a 3D6, 3 six-sided dice added together
int ThreeDSix() 
{
  int x = 0;
  for(int i = 0; i < 3; i++)
  {
    x += PLAY.Dsix();
  }
  return x;
}

//Rolls a 2D6+6, 2 six-sided dice added together plus 6
int TwoDSixPlusSix() 
{ 
  int x = 0;
  for(int i = 0; i < 2; i++)
  {
    x += PLAY.Dsix();
  }
  return x+6;
}


//BRP_human_base class
//Constructor to hold Characteristics, 
BRP_human_base::BRP_human_base(int a, int b, int c, int d, int e, int x, int y) 
{
  STR = a;
  CON = b;
  POW = c;
  DEX = d;
  CHA = e;
  INT = x;
  SIZ = y;

}

//Optional settings 
void BRP_human_base::SettingsSwitches()
{
  EDUCATION_STAT = true;
  SKILL_CATEGORY = false;
  SKILL_CATEGORY_SIMPLE = false;
  WINGED_CHARACTER = false;
  INCREASED_PERSONAL_SKILL_POINTS = false;
  POWER_LEVEL = 0;
}

//EDU Characteristic
int BRP_human_base::EDUstat()
{
  if (EDUCATION_STAT == true)
    {
      EDU = 0;
      EDU = TwoDSixPlusSix();
      return EDU;
    }
  else 
    {
      return 0;
    }
}

//Returns a STAT times 5, for a percentage roll
//This is at standard difficulty
int BRP_human_base::CharacteristicRoll(int r)
{
  int CharRoll = r * 5;
  return CharRoll;
}

//Generates starting age
//Will need to expand to allow input from user and modifiers for higher and lower ages
int BRP_human_base::Born()
{
  int startage = 17+PLAY.Dsix();

  Age = startage;

  return Age;
}

//Calculates Damage Bonus
std::string BRP_human_base::DamageBonus()
{
  int Db = STR + SIZ;
    
  std::map<int, std::string> DamageModifierTable;
  DamageModifierTable[0] = "Error";
  DamageModifierTable[1] = "-1D6";
  DamageModifierTable[2] = "-1D4";
  DamageModifierTable[3] = "None";
  DamageModifierTable[4] = "+1D4";
  DamageModifierTable[5] = "+1D6";
  DamageModifierTable[6] = "+2D6";
  DamageModifierTable[7] = "+3D6";
  DamageModifierTable[8] = "Ea. +16"; //need to edit result 8, adding 1d6 for every 16th value above 73 (double check the book)

  int DMT;
  
  if (Db >= 2 && Db <= 12) {DMT = 1;}
  else if (Db >= 13 && Db <= 16) {DMT = 2;}
  else if (Db >= 17 && Db <= 24) {DMT = 3;}
  else if (Db >= 25 && Db <= 32) {DMT = 4;}
  else if (Db >= 33 && Db <= 40) {DMT = 5;}
  else if (Db >= 41 && Db <= 56) {DMT = 6;}
  else if (Db >= 57 && Db <= 72) {DMT = 7;}
  else if (Db >= 73) {DMT = 8;}
  else {DMT = 0;}

  DamBonus = DamageModifierTable[DMT];
  
  return DamBonus;
}

//Calculates Hit Points
int BRP_human_base::HitPoints()
{
  HP = ceil((CON + SIZ)/2); 
  return HP;
}

//Calculates Major Wounds
int BRP_human_base::MajorWounds()
{
  MW = ceil(HP/2);
  return MW;
}

//Determines character's distinctive features based on CHA
std::string BRP_human_base::DistinctiveFeatures()
{
  int DFs;
  std::string W;

  if (CHA <= 3 || CHA >= 17) {DFs = 4;}
  else if (CHA >= 4 && CHA <= 7) {DFs = 3;}
  else if (CHA >= 8 && CHA <= 9) {DFs = 2;}
  else if (CHA >= 10 && CHA <= 11) {DFs = 1;}
  else if (CHA >= 12 && CHA <= 14) {DFs = 2;}
  else if (CHA >= 15 && CHA <= 16) {DFs = 3;}
  else {DFs = 0;} 

  //Need another list for each Feature Type
  std::map<int, std::string> FeatureTypeTable;
  FeatureTypeTable[0] = "Error";
  FeatureTypeTable[1] = "Hair on head";
  FeatureTypeTable[2] = "Facial hair";
  FeatureTypeTable[3] = "Facial feature";
  FeatureTypeTable[4] = "Expression";
  FeatureTypeTable[5] = "Clothes";
  FeatureTypeTable[6] = "Bearing";
  FeatureTypeTable[7] = "Speech";
  FeatureTypeTable[8] = "Arms and legs";
  FeatureTypeTable[9] = "Torso";
  FeatureTypeTable[10] = "Legs and feet";

  //need to find logic to have two items seperated by 'and' and three plus items seperated by ',' and 'and' while ending in ''
  for (int i = 0; i < DFs; i++) 
  {
    int Q = PLAY.Dten();
    if (DFs == 2) {W = (i > 0) ? "": " and ";}
    else if (DFs == 3) {W = (i > 0) ? "": " and ";}
    else {W = "";} //DFs == 1
    //std::string W = (i >= 1) ? "": " and ";
    std::string WIP = FeatureTypeTable[Q] + W;
    UnitedFeatures += WIP;
  }

  return UnitedFeatures;
}

//Profession skill points
int BRP_human_base::ProSkillPointsPool()
{
  if (POWER_LEVEL == 1) //Heroic game
    {
      if (EDUCATION_STAT == true) 
        {
          return EDU*25;
        }
      else
        {
        return 325;
        }
    }
  else if (POWER_LEVEL == 2) //Epic game
    {
      if (EDUCATION_STAT == true) 
        {
          return EDU*30;
        }
      else
        {
          return 400; 
        }
    }
  else if (POWER_LEVEL == 3) //Superhuman game
    {
      if (EDUCATION_STAT == true) 
        {
          return EDU*40;
        }
      else
        {
         return 500;
        }
    }
  else //default for Nomral game
  {
    if (EDUCATION_STAT == true) 
      {
        return EDU*20;
      }
    else
      {
        return 250;
      }
  }
}

//Personal skill points
int BRP_human_base::PerSkillPonitsPool()
{
  int PPP = 0;
  if (INCREASED_PERSONAL_SKILL_POINTS == true)
    {
      if (POWER_LEVEL == 1) //Heroic game
        {
          PPP = INT*15;
        }
      else if (POWER_LEVEL == 2) //Epic game
        {
          PPP = INT*20;
        }
      else if (POWER_LEVEL == 3) //Superhuman game
        {
          PPP = INT*25;
        }
    }
  else
    {
      PPP = INT * 10; //Default nNrmal game
    }
  return PPP;
}

//Determines character's profession
void BRP_human_base::Professions()
{
  std::string jobs[44] = {"Artist", "Assassin", "Athlete", "Beggar", "Clerk", "Computer Tech", "Crafter", "Criminal", "Detective", "Doctor", "Engineer", "Entertainer", "Explorer", "Farmer", "Gambler", "Herder", "Hunter", "Journalist", "Laborer", "Lawkeeper", "Lawyer", "Mechanic", "Merchant", "Noble", "Occultist", "Pilot", "Politician", "Priest", "Sailor", "Scholar", "Scientist", "Servant", "Shaman", "Slave", "Soldier", "Spy", "Student", "Teacher", "Technician", "Thief", "Tribesperson", "Warrior", "Wizard", "Writer"};

  int Hired = rand() % 44;

  Profession = jobs[Hired];

  std::string pay[5] = {"Destitute", "Poor", "Average", "Affluent", "Wealthy"};
 
  int Earned = rand() % 8;

  Wealth = "Broke";


  
  //I hate this series of if statements, these has to be a smarter way to do this. Easier for another person to change at a glance...
  
  //Artist
  if (Hired == 0) 
    {Earned = rand() % 9; if (Earned == 0 ){Wealth = "Destitute";} else if (Earned >= 1 && Earned <= 3){Wealth = "Poor";} else if (Earned >= 4 && Earned <= 6){Wealth = "Average";} else if (Earned == 7){Wealth = "Affluent";} else if (Earned == 8){Wealth = "Wealthy";};}
  //Assassin  
  else if (Hired == 1) 
    {if (Earned <= 3){Wealth = "Average";} else {Wealth = "Wealthy";};}
  //Athlete wip 
  else if (Hired == 2) 
    {if (Earned == 0 ){Wealth = "Destitute";} else if (Earned >= 1 && Earned <= 3){Wealth = "Poor";} else if (Earned >= 4 && Earned <= 6){Wealth = "Average";} else if (Earned == 7){Wealth = "Affluent";} else if (Earned == 8){Wealth = "Wealthy";};}
  //Beggar wip
  else if (Hired == 3) 
    {if (Earned == 0 ){Wealth = "Destitute";} else if (Earned >= 1 && Earned <= 3){Wealth = "Poor";} else if (Earned >= 4 && Earned <= 6){Wealth = "Average";} else if (Earned == 7){Wealth = "Affluent";} else if (Earned == 8){Wealth = "Wealthy";};}


}

//Determines character's gender 
std::string BRP_human_base::RandGender()
{
  int X = PLAY.Donehundred();

  //50% Female, 49% Male, 1% Non-Binary, hyper simplified but I lack enough real world data and I want a chance for non-CIS genders
  if (X == 100) {Gender = "Non-Binary";}
  else if (X >= 51) {Gender = "Male";}
  else {Gender = "Female";}
  
  return Gender;
}

//Determines character's hand dominance 
std::string BRP_human_base::HandDom()
{
  int Odds = PLAY.Donehundred();

  //83% Right-Handed, 13% Left-Handed, 3% Ambidextrous, 1% Cross-Dominant; based on UN data
  if (Odds == 100) {Handedness = "Cross-Dominant";}
  else if (Odds >= 97) {Handedness = "Ambidextrous";}
  else if (Odds >= 1 && Odds <= 13) {Handedness = "Left-Handed";}
  else {Handedness = "Right-Handed";}
  
  return Handedness;
}

//Determines character's Height and Weight 
void BRP_human_base::HeightandWeight()
{
  //2D-array of height and weight outcomes
  std::string HTandWT[2][5] = 
{
  {"Tiny","Short","Average","Tall","Towering"},
  {"Frail","Thin","Average","Overweight","Obese"}
};

  //poor if statement just to use the array. should adjust results based on CON and maybe random chance
    //Average outcome
  if (SIZ >= 10 && SIZ <= 13) {Height = HTandWT[0][2], Weight = HTandWT[1][2];}
    //Low end outcome, Tiny/Frail
  else if (SIZ < 10) {Height = HTandWT[0][1], Weight = HTandWT[1][1];}
    //High end outcome, Tall/Overweight
  else if (SIZ >= 14 && SIZ <= 17) {Height = HTandWT[0][3], Weight = HTandWT[1][3];}
    //Default outcome, Towering/Obese
  else {Height = HTandWT[0][4], Weight = HTandWT[1][4];}
}

//Primary Skill Category
int BRP_human_base::Skill_Category_Primary(int x)
{
  //argument x = one STAT, +1 for every point over 10, -1 for every point under 10, 0 at 10
  int P = 0;
  if (x >= 10)
   {
     int z = x-10;
     for (int i = 0; i < z; i++)
     {
       P++;
     }
   }
  else 
  {
    int z = 10-x;
     for (int i = 0; i < z; i++)
     {
       P--;
     }
  }
  return P;
}

//Secondary Skill Category
int BRP_human_base::Skill_Category_Secondary(int x)
{
  //argument x = one STAT, +1 for every 2 points over 10, -1 for every 2 points under 10, 0 at 10
  int P = 0;
  if (x >= 10)
   {
     x = x - 10;
     int z = std::floor(x / 2);
     for (int i = 0; i < z; i++)
     {
       P++;
     }
   }
  else 
  {
    int z = std::floor((10-x) / 2);
     for (int i = 0; i < z; i++)
     {
       P--;
     }
  }
  return P;
}

//Negative Skill Category
int BRP_human_base::Skill_Category_Negative(int x)
{
  //argument x = one STAT (SIZ is the only one), 11 for every point over 10, +1 for every point under 10, 0 at 10
  int P = 0;
  if (x >= 10)
   {
     int z = x-10;
     for (int i = 0; i < z; i++)
     {
       P--;
     }
   }
  else 
  {
    int z = 10-x;
     for (int i = 0; i < z; i++)
     {
       P++;
     }
  }
  return P;
}

//Handles all skills and skill categorys 
void BRP_human_base::Skills()
{
  //special base values for skills
  int DodgeBase = DEX*2; //Dodge
  if (WINGED_CHARACTER == true) //Fly
    {int FlyBase = DEX*4;} 
  else{int FlyBase = ceil(DEX/2);}
  int GamingBase = INT+POW; //Gaming
  if (EDUCATION_STAT == true) //Own Language
    {int Language0Base = EDU*5;}
  else{int Language0Base = INT*5;}
  int ProjectionBase = DEX*2; //Projection

  //Skill Category rules
  Combat_skillcategory = 0;    
  Communication_skillcategory = 0;
  Manipulation_skillcategory = 0;
  Mental_skillcategory = 0;
  Perception_skillcategory = 0;
  Physical_skillcategory = 0;
  
  if (SKILL_CATEGORY == true && SKILL_CATEGORY_SIMPLE == false) 
  {
    int A = Skill_Category_Primary(DEX);
    int B = Skill_Category_Primary(INT);
    
    int E = Skill_Category_Secondary(INT);
    int F = Skill_Category_Secondary(STR);
    int G = Skill_Category_Secondary(POW);
    int J = Skill_Category_Secondary(CHA);
    int H = Skill_Category_Secondary(CON);
    int I = 0;
    if (EDUCATION_STAT == true) 
      {int I = Skill_Category_Secondary(EDU);}
    
    int Z = Skill_Category_Negative(SIZ);

    //Mental Skill Category also addes in EDU as a secondary characteristic but ommits it if EDU is not used
    //will need an if statement for when EDU is used
    Combat_skillcategory = (A + B + F);    
    Communication_skillcategory = (B + G + J);
    Manipulation_skillcategory = (A + E + F);
    Mental_skillcategory = (B + G + I);
    Perception_skillcategory = (B + G + H);
    Physical_skillcategory = (A + F + H + Z);
  }

  //Simple Skill Category rules
   if (SKILL_CATEGORY == true && SKILL_CATEGORY_SIMPLE == true) 
   {
    //Takes a relevant STAT and divides it by 2 rounded up
    int D = ceil(DEX/2);
    int C = ceil(CHA/2);
    int I = ceil(INT/2);
    int P = ceil(POW/2);
    int S = ceil(STR/2);
     
    Combat_skillcategory = D;    
    Communication_skillcategory = C;
    Manipulation_skillcategory = D;
    Mental_skillcategory = I;
    Perception_skillcategory = P;
    Physical_skillcategory = S;
   } 

  //Mod changes... maybe do a for loop in the skill category if statement
  skill_APPR.SkillMod += {skill_APPR.SkillBase + Mental_skillcategory};

    
  //map of all skills with; name, subtype, base%, and last value to be modifyed
  //This still seems too unweildly, especially with subtypes and Bases set by weapons
  //Should Each type also have skill category assigned too it as well?
  SkillTable["Appraise"] = { "Appraise", "", 15, 0};
  SkillTable["Art0"] = { "Art", "", 5, 0};
  SkillTable["Artillery0"] = { "Artillery", "", 0, 0};
  SkillTable["Bargain"] = { "Bargain", "", 5, 0};
  SkillTable["Brawl"] = { "Brawl", "", 25, 0};
  SkillTable["Climb"] = { "Climb", "", 40, 0};
  SkillTable["Command"] = { "Command", "", 5, 0};
  SkillTable["Craft0"] = { "Craft", "", 5, 0};
  SkillTable["Demolition"] = { "Demolition", "", 1, 0};
  SkillTable["Disguise"] = { "Disguise", "", 1, 0};
  SkillTable["Dodge"] = { "Dodge", "", DodgeBase, 0};
  SkillTable["Drive0"] = { "Drive", "", 20, 0};
  SkillTable["Drive1"] = { "Drive", "", 1, 0};
  SkillTable["Energy Weapon0"] = { "Energy Weapon", "", 0, 0};
  SkillTable["Etiquette0"] = { "Etiquette", "", 5, 0};

  //varibles to call individule skills
  skill_APPR = SkillTable.at("Appraise");
  skill_ART0 = SkillTable.at("Art0");
  skill_DODG = SkillTable.at("Dodge");
  
}

//Gets the character's name
void BRP_human_base::CharName()
{
  std::cout << "\nWhat is the character's name?\n";
  std::getline(std::cin >> std::ws, CN); 
}

//Gets the user's name
void BRP_human_base::PlayerName()
{
  std::cout << "\nWhat is your name?\n";
  std::getline(std::cin >> std::ws, PN);
}

//Generates a fully randomized character
void BRP_human_base::fullrandom(RandomSetUp& WOW)
{
  SettingsSwitches();
  EDUstat();
  Born();
  Professions();
  RandGender();
  Skills();
  HandDom();
  HitPoints();
  MajorWounds();
  DamageBonus();
  DistinctiveFeatures();
  HeightandWeight();
  
  std::cout << "\n" << std::endl;
  std::cout << "Starting Age: " << Age << "\t" << "Works as a " << Wealth << " " << Profession << std::endl;
  std::cout << "Gender: " << Gender << "\t" << "Handedness: " << Handedness << std::endl;
  std::cout << "Height: " << Height << "\t" << "Weight: " << Weight << std::endl;
  std::cout << "STR " << STR << "\t" << "Effort roll " << CharacteristicRoll(STR) << "%\t\t\t" << "INT " << INT << "\t" << "Idea roll " << CharacteristicRoll(INT) << "%" << std::endl; 
  std::cout << "CON " << CON << "\t" << "Stamina roll " << CharacteristicRoll(CON) << "%\t\t" << "CHA " << CHA << "\t" << "Charm roll " << CharacteristicRoll(CHA) << "%" << std::endl;
  std::cout << "DEX " << DEX << "\t" << "Agility roll " << CharacteristicRoll(DEX) << "%\t\t" << "POW " << POW << "\t" << "Luck roll " << CharacteristicRoll(POW) << "%" << std::endl;  
  if (EDUCATION_STAT == true) 
  {std::cout << "EDU " << EDU << "\t" << "Knoweledge roll " << CharacteristicRoll(EDU) << "%\t\t" << "SIZ " << SIZ << std::endl; }
  else
  {std::cout << "SIZ " << SIZ << std::endl;}
  std::cout << "HP: " << HP << " with Major Would occuring at " << MW << " HP" << std::endl;
  std::cout << "Damage Bonus of " << DamBonus << std::endl;
  std::cout << "\nThey have distintive " << UnitedFeatures << "." <<std::endl;
  std::cout << "\nProfessional Skill Points Pool: "  << ProSkillPointsPool() << std::endl;
  std::cout << "Personal Skill Points Pool: "  << PerSkillPonitsPool() << std::endl;
  std::cout << "COMMUNICATION (" << Communication_skillcategory << "%)" << "\t\t\t" << "MENTAL (" << Mental_skillcategory << "%)" << "\t\t\t" << "PHYSICAL (" << Physical_skillcategory << "%)" << "\t\t\t" << std::endl;
  std::cout << "MANIPULATION (" << Manipulation_skillcategory << "%)" << "\t\t\t" << "PERCEPTION (" << Perception_skillcategory << "%)" << "\t\t\t" << "COMBAT (" << Combat_skillcategory << "%)" << "\t\t\t" << std::endl;
  std::cout << "Skills" << std::endl;
  std::cout << skill_APPR.SkillName << " (" << skill_APPR.SkillBase << "%)" << std::endl;
  std::cout << skill_ART0.SkillName << " (" << skill_ART0.SkillBase << "%)" << std::endl;
  std::cout << skill_DODG.SkillName << " (" << skill_DODG.SkillBase << "%)" << std::endl;
  
  std::cout << "\n\nSeed: " << WOW.currentSeed;
} 

//Prints a txt file character sheet
void BRP_human_base::printChar(RandomSetUp& WOW)
{
  std::string BRPFilePath = "Characters/BRP/";
  
  std::string BRPCharFileName = BRPFilePath + CN + "_by_" + PN + ".txt";
  
  std::ofstream BRPText(BRPCharFileName,std::ofstream::out);

  BRPText << "===========================================================" << std::endl;
  BRPText << "\t\t\tPERSONAL" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "Name: " << CN << "\t\t" << "Player: " << PN << std::endl;
  BRPText << "Culture: " << "Human" << "\t\t" << "Gender: " << Gender << std::endl;
  BRPText << "Handedness: " << Handedness << "\t" << "Height: " << Height << "\t" << "Weight: " << Weight << std::endl;
  BRPText << "Profession: " << Profession << "\t\t" << "Wealth: " << Wealth << std::endl;
  BRPText << "Gods/Religion: " << "Agnostic" << std::endl;
  BRPText << "\nThey have distintive " << UnitedFeatures << "." <<std::endl;
  BRPText << "MOV: " << 10 << "\t\t" << "Age: " << Age << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "\t\t\tCHARACTERISTICS" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "STR " << std::setw(2) << std::setfill('0') << STR << "\t" << "Effort roll " << CharacteristicRoll(STR) << "%\t\t\t" << "INT " << std::setw(2) << std::setfill('0') << INT << "\t" << "Idea roll " << CharacteristicRoll(INT) << "%" << std::endl; 
  BRPText << "CON " << std::setw(2) << std::setfill('0') << CON << "\t" << "Stamina roll " << CharacteristicRoll(CON) << "%\t\t" << "CHA " << std::setw(2) << std::setfill('0') << CHA << "\t" << "Charm roll " << CharacteristicRoll(CHA) << "%" << std::endl;
  BRPText << "DEX " << std::setw(2) << std::setfill('0') << DEX << "\t" << "Agility roll " << CharacteristicRoll(DEX) << "%\t\t" << "POW " << std::setw(2) << std::setfill('0') << POW << "\t" << "Luck roll " << CharacteristicRoll(POW) << "%" << std::endl;  
  if (EDUCATION_STAT == true) 
  {BRPText << "EDU " << std::setw(2) << std::setfill('0') << EDU << "\t" << "Knowledge roll " << CharacteristicRoll(EDU) << "%\t";} 
  BRPText << "SIZ " << std::setw(2) << std::setfill('0') << SIZ << "\t" << "Damage Bonus of " << DamBonus << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "\t\t\tHIT POINTS" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "HP: " << HP << " with Major Would occuring at " << MW << " HP" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "\t\t\tSKILLS" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "Professional Skill Points Pool: "  << ProSkillPointsPool() << std::endl;
  BRPText << "Personal Skill Points Pool: "  << PerSkillPonitsPool() << std::endl;
  
  BRPText << skill_APPR.SkillName << " (" << skill_APPR.SkillBase << "%)" << "\t\t\t" << skill_APPR.SkillMod << "%" << std::endl;
  
  BRPText << "COMMUNICATION (" << Communication_skillcategory << "%)" << "\t\t\t" << "MENTAL (" << Mental_skillcategory << "%)" << "\t\t\t" << "PHYSICAL (" << Physical_skillcategory << "%)" << "\t\t\t" << std::endl;
  BRPText << "MANIPULATION (" << Manipulation_skillcategory << "%)" << "\t\t\t" << "PERCEPTION (" << Perception_skillcategory << "%)" << "\t\t\t" << "COMBAT (" << Combat_skillcategory << "%)"  << "\t\t\t" << std::endl;
  
  BRPText << "\n\nSeed: " << WOW.currentSeed;
  
  BRPText.close();
}