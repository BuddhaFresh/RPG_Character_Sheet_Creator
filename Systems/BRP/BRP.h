#pragma once
#include "../../diceroller.h"
#include "../../menus.h"
#include <map>
#include <math.h>
#include <vector>
#include <iomanip>
#include <string>


//Function declarations
void FolderOriginBRP();
int ThreeDSix();
int TwoDSixPlusSix();

//Skill struct
struct SkillData 
{
  std::string SkillName;
  std::string SubSkillName;
  int SkillBase;
  int SkillMod;
};

//work in progress
struct WealthRange
{
  std::string WealthLevel;
  int WealthWeight;
};



class BRP_human_base
{
private:
  bool EDUCATION_STAT;
  bool SKILL_CATEGORY;
  bool SKILL_CATEGORY_SIMPLE;
  bool WINGED_CHARACTER;
  bool INCREASED_PERSONAL_SKILL_POINTS;
  int POWER_LEVEL;
  int STR;
  int CON;
  int POW;
  int DEX;
  int INT;
  int SIZ;
  int CHA;
  int EDU;
  int Age;
  int HP;
  int MW;

  std::string DamBonus;
  std::string Profession;
  std::string Wealth;  
  std::string UnitedFeatures;
  std::string Gender;
  std::string Handedness;
  std::string Height;
  std::string Weight;

  int Combat_skillcategory;
  int Communication_skillcategory;
  int Manipulation_skillcategory;
  int Mental_skillcategory;
  int Perception_skillcategory;
  int Physical_skillcategory;


  void SettingsSwitches();
  int EDUstat();
  void Skills();
  int CharacteristicRoll(int r);
  int Born();
  std::string DamageBonus();
  int HitPoints();
  int MajorWounds();
  std::string DistinctiveFeatures();
  void Professions();
  std::string RandGender();
  std::string HandDom();
  int ProSkillPointsPool();
  int PerSkillPonitsPool();
  void HeightandWeight();
  int Skill_Category_Primary(int x);
  int Skill_Category_Secondary(int x);
  int Skill_Category_Negative(int x);

  std::map<std::string, SkillData>SkillTable;
  SkillData skill_APPR;
  SkillData skill_ART0;
  SkillData skill_DODG;


public:
  BRP_human_base(int a, int b, int c, int d, int e, int x, int y);

  void CharName();
  std::string CN;
  void PlayerName();
  std::string PN;



  void printChar(RandomSetUp& WOW);
  void fullrandom(RandomSetUp& WOW);
};