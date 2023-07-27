#include "../../menus.h"
#include "../../diceroller.h"
#include "BRP.h"



//GOAL FOR SCRIPT
//everything needed to make a standard Basic Role-Playing Character
//Needs to have attrabutes, diraived stats, list of relivent features, equipment(just a basic set for now)
//class BRP char with roll inputs


//Classes
//RandomSetUp CALL;
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

//Profession Wealth System
//Section for Profession Data Map to determine Profession wealth
struct WealthLevel 
{
  std::string level;
  int weight;
};

struct ProfessionData 
{
  std::string professionName;
  std::vector<WealthLevel> wealthLevels;
};

std::map<std::string, ProfessionData> professionDataMap;

//Number after Wealth Level is the weight when determines chance to be at that level
void initializeProfessionData() 
{
  professionDataMap["Artist"] = {"Artist", {{"Destitute", 1}, {"Poor", 4}, {"Average", 5}, {"Affluent", 2}, {"Wealthy", 1}}};
  professionDataMap["Assassin"] = {"Assassin", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Athlete"] = {"Athlete", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Beggar"] = {"Beggar", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Clerk"] = {"Clerk", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Computer Tech"] = {"Computer Tech", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Crafter"] = {"Crafter", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Criminal"] = {"Criminal", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Detective"] = {"Detective", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Doctor"] = {"Doctor", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Engineer"] = {"Engineer", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Entertainer"] = {"Entertainer", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Explorer"] = {"Explorer", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Farmer"] = {"Farmer", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Gambler"] = {"Gambler", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Herder"] = {"Herder", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Hunter"] = {"Hunter", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Journalist"] = {"Journalist", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Laborer"] = {"Laborer", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Lawkeeper"] = {"Lawkeeper", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Lawyer"] = {"Lawyer", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Mechanic"] = {"Mechanic", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Merchant"] = {"Merchant", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Noble"] = {"Noble", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Occultist"] = {"Occultist", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Pilot"] = {"Pilot", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Politician"] = {"Politician", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Priest"] = {"Priest", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Sailor"] = {"Sailor", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Scholar"] = {"Scholar", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Scientist"] = {"Scientist", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Servant"] = {"Servant", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Shaman"] = {"Shaman", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Slave"] = {"Slave", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Soldier"] = {"Soldier", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Spy"] = {"Spy", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Student"] = {"Student", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Teacher"] = {"Teacher", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Technician"] = {"Technician", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Thief"] = {"Thief", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Tribesperson"] = {"Tribesperson", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Warrior"] = {"Warrior", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
  professionDataMap["Wizard"] = {"Wizard", {{"Destitute", 0}, {"Poor", 0}, {"Average", 10}, {"Affluent", 0}, {"Wealthy", 0}}};
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

int BRP_human_base::CharacteristicRoll(int r)
{
  int CharRoll = r * 5;
  return CharRoll;
}

//Will need to expand to allow input from user and modifiers for higher and lower ages
int BRP_human_base::Born()
{
  int startage = 17+PLAY.Dsix();

  Age = startage;

  return Age;
}

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

int BRP_human_base::HitPoints()
{
  HP = ceil((CON + SIZ)/2); 
  return HP;
}

int BRP_human_base::MajorWounds()
{
  MW = ceil(HP/2);
  return MW;
}

std::string BRP_human_base::DistinctiveFeatures()
{
  int DFs;
  std::string W;

  if (CHA <= 3 || ) {DFs = 4;}
  else if (CHA >= 4 && CHA <= 7) {DFs = 3;}
  else if (CHA >= 8 && CHA <= 9) {DFs = 2;}
  else if (CHA >= 10 && CHA <= 11) {DFs = 1;}
  else if (CHA >= 12 && CHA <= 14) {DFs = 2;}
  else if (CHA >= 15 && CHA <= 16) {DFs = 3;}
  else if (CHA >= 17) {DFs = 4;}
  else {DFs = 0;} 

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

int BRP_human_base::ProSkillPointsPool()
{
  return 250; //default for nomral game, need to have options for other 
}

int BRP_human_base::PerSkillPonitsPool()
{
  int PPP = INT * 10;
  return PPP;
}

void BRP_human_base::Professions()
{
  std::string jobs[44] = {"Artist", "Assassin", "Athlete", "Beggar", "Clerk", "Computer Tech", "Crafter", "Criminal", "Detective", "Doctor", "Engineer", "Entertainer", "Explorer", "Farmer", "Gambler", "Herder", "Hunter", "Journalist", "Laborer", "Lawkeeper", "Lawyer", "Mechanic", "Merchant", "Noble", "Occultist", "Pilot", "Politician", "Priest", "Sailor", "Scholar", "Scientist", "Servant", "Shaman", "Slave", "Soldier", "Spy", "Student", "Teacher", "Technician", "Thief", "Tribesperson", "Warrior", "Wizard", "Writer"};

  int Hired = rand() % 44;

  Profession = jobs[Hired];

  std::string payscales[5] = {"Destitute", "Poor", "Average", "Affluent", "Wealthy"};
 
  int Earned = rand() % 10;

  Wealth = "Broke";
  
  // Get the wealth level ranges for the profession
  std::vector<WealthLevel>wealthLevels = professionDataMap[Profession].wealthLevels;

  // Calculate the total weight of all wealth levels for the profession
  int totalWeight = 0;
  for (auto wealthLevel : wealthLevels) 
  {
    totalWeight += wealthLevel.weight;
  }

  // Generate a random number between 0 and totalWeight - 1
  int randomValue = rand() % totalWeight;

  // Find the corresponding wealth level based on the random number and weights
  int currentWeight = 0;
  for (auto wealthLevel : wealthLevels) 
  {
    currentWeight += wealthLevel.weight;
    if (randomValue < currentWeight) 
    {
      Wealth = wealthLevel.level;
      break;
    }
  }
}

std::string BRP_human_base::RandGender()
{
  int X = PLAY.Donehundred();
  std::string Z;

  if (X >= 51) {Z = "Male";}
  else {Z = "Female";}

  Gender = Z;
  
  return Gender;
}

std::string BRP_human_base::HandDom()
{
  int Odds = PLAY.Donehundred();

  if (Odds == 0) {Handedness = "Cross-Dominant";}
  else if (Odds >= 97) {Handedness = "Ambidextrous";}
  else if (Odds >= 1 && Odds <= 13) {Handedness = "Left-Handed";}
  else {Handedness = "Right-Handed";}
  
  return Handedness;
}

void BRP_human_base::HeightandWeight()
{
  //2D-array of height and weight outcomes
  std::string HTandWT[2][5] = 
{
  {"Tiny","Short","Average","Tall","Towering"},
  {"Frail","Thin","Average","Overweight","Obese"}
};

  //poor if statement just to use the array. should adjust results based on CON and maybe random chance
  if (SIZ >= 10 && SIZ <= 13) {Height = HTandWT[0][2], Weight = HTandWT[1][2];}
  else if (SIZ < 10) {Height = HTandWT[0][1], Weight = HTandWT[1][1];}
  else if (SIZ >= 14 && SIZ <= 17) {Height = HTandWT[0][3], Weight = HTandWT[1][3];}
  else {Height = HTandWT[0][4], Weight = HTandWT[1][4];}
}

void BRP_human_base::Skills()
{
  //stores base skill values and changes them based on GM setting
  
}

void BRP_human_base::CharName()
{
  std::cout << "\nWhat is the character's name?\n";
  std::getline(std::cin >> std::ws, CN); 
}

void BRP_human_base::PlayerName()
{
  std::cout << "\nWhat is your name?\n";
  std::getline(std::cin >> std::ws, PN);
}

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
  BRPText << "SIZ " << std::setw(2) << std::setfill('0') << SIZ << "\t\t\t\t\t" << "Damage Bonus of " << DamBonus << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "\t\t\tHIT POINTS" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "HP: " << HP << " with Major Would occuring at " << MW << " HP" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "\t\t\tSKILLS" << std::endl;
  BRPText << "===========================================================" << std::endl;
  BRPText << "Professional Skill Points Pool: "  << ProSkillPointsPool() << std::endl;
  BRPText << "Personal Skill Points Pool: "  << PerSkillPonitsPool() << std::endl;
  BRPText << "COMMUNICATION"  << "\t\t\t" << "MENTAL"  << "\t\t\t" << "PHYSICAL"  << "\t\t\t" << std::endl;
  BRPText << "MANIPULATION"  << "\t\t\t" << "PERCEPTION"  << "\t\t\t" << "COMBAT"  << "\t\t\t" << std::endl;
  
  BRPText << "\n\nSeed: " << WOW.currentSeed;
  
  BRPText.close();
}

void BRP_human_base::fullrandom(RandomSetUp& WOW)
{
  Born();
  Professions();
  RandGender();
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
  std::cout << "SIZ " << SIZ << std::endl;
  std::cout << "HP: " << HP << " with Major Would occuring at " << MW << " HP" << std::endl;
  std::cout << "Damage Bonus of " << DamBonus << std::endl;
  std::cout << "Professional Skill Points Pool: "  << ProSkillPointsPool() << std::endl;
  std::cout << "Personal Skill Points Pool: "  << PerSkillPonitsPool() << std::endl;
  std::cout << "\nThey have distintive " << UnitedFeatures << "." <<std::endl;
  std::cout << "\n\nSeed: " << WOW.currentSeed;
} 