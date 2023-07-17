#include "../../menus.h"
#include "../../diceroller.h"
#include "BRP.h"
#include <map>
#include <math.h>


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
int BRP_human_base::Age()
{
  int age = 17+PLAY.Dsix();
  return age;
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

  std::string x = DamageModifierTable[DMT];
  
  return x;
}

int BRP_human_base::HitPoints()
{
  int HP = (CON + SIZ)/2; //round up?
  return HP;
}

int BRP_human_base::MajorWounds()
{
  int MW = ceil(HitPoints()/2); //ceil rounds up
  return MW;
}

std::string BRP_human_base::DistinctiveFeatures()
{
  int DFs;
  std::string W;
  std::string UnitedFeatures;

  if (CHA <= 3) {DFs = 4;}
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
  return 250; //default for nomral game, need to have options
}

int BRP_human_base::PerSkillPonitsPool()
{
  int PPP = INT * 10;
  return PPP;
}

void BRP_human_base::CharName()
{
  std::cout << "\nWhat is the character's name?\n";
  std::cin >> CN; 
}

void BRP_human_base::PlayerName()
{
  std::cout << "\nWhat is your name?\n";
  std::cin >> PN;
}



void BRP_human_base::fullrandom(RandomSetUp& WOW)
{
  CharName();
  std::cout << "\n" << std::endl;
  std::cout << "Name: " << CN << "\t\t" << "Player: " << PN << std::endl;
  std::cout << "Age: " << Age() << std::endl;
  std::cout << "STR " << STR << "\t" << "Effort roll " << CharacteristicRoll(STR) << "%\t\t\t" << "INT " << INT << "\t" << "Idea roll " << CharacteristicRoll(INT) << "%" << std::endl; 
  std::cout << "CON " << CON << "\t" << "Stamina roll " << CharacteristicRoll(CON) << "%\t\t" << "CHA " << CHA << "\t" << "Charm roll " << CharacteristicRoll(CHA) << "%" << std::endl;
  std::cout << "DEX " << DEX << "\t" << "Agility roll " << CharacteristicRoll(DEX) << "%\t\t" << "POW " << POW << "\t" << "Luck roll " << CharacteristicRoll(POW) << "%" << std::endl;  
  std::cout << "SIZ " << SIZ << std::endl;
  std::cout << "HP: " << HitPoints() << " with Major Would occuring at " << MajorWounds() << " HP" << std::endl;
  std::cout << "Damage Bonus of " << DamageBonus() << std::endl;
  std::cout << "Professional Skill Points Pool: "  << ProSkillPointsPool() << std::endl;
  std::cout << "Personal Skill Points Pool: "  << PerSkillPonitsPool() << std::endl;
  std::cout << "\nThey have distintive " << DistinctiveFeatures() << "." <<std::endl;
  std::cout << "\n\nSeed: " << WOW.currentSeed;
  printChar(); 
} 

void BRP_human_base::printChar()
{
  std::ofstream BRPText("Characters/BRP/test.txt");
  
  BRPText << "Name: " << CN << "\t\t" << "Player: " << PN << std::endl;
  BRPText << "Age: " << Age() << std::endl;
  BRPText << "STR " << STR << "\t" << "Effort roll " << CharacteristicRoll(STR) << "%\t\t\t" << "INT " << INT << "\t" << "Idea roll " << CharacteristicRoll(INT) << "%" << std::endl; 
  BRPText << "CON " << CON << "\t" << "Stamina roll " << CharacteristicRoll(CON) << "%\t\t" << "CHA " << CHA << "\t" << "Charm roll " << CharacteristicRoll(CHA) << "%" << std::endl;
  BRPText << "DEX " << DEX << "\t" << "Agility roll " << CharacteristicRoll(DEX) << "%\t\t" << "POW " << POW << "\t" << "Luck roll " << CharacteristicRoll(POW) << "%" << std::endl;  
  BRPText << "SIZ " << SIZ << std::endl;
  BRPText << "HP: " << HitPoints() << " with Major Would occuring at " << MajorWounds() << " HP" << std::endl;
  BRPText << "Damage Bonus of " << DamageBonus() << std::endl;
  BRPText << "Professional Skill Points Pool: "  << ProSkillPointsPool() << std::endl;
  BRPText << "Personal Skill Points Pool: "  << PerSkillPonitsPool() << std::endl;
  BRPText << "\nThey have distintive " << DistinctiveFeatures() << "." <<std::endl;
  
  BRPText.close();
}
//maybe after fullrandom ask if user wishes to save and then ask for char name, can make text doc with the saved info.