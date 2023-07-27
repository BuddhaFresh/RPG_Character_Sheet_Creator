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

//Class declarations

class BRP_human_base
{
public:
  BRP_human_base(int a, int b, int c, int d, int e, int x, int y);
  int STR;
  int CON;
  int POW;
  int DEX;
  int INT;
  int SIZ;
  int CHA;
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
  std::string PN;
  std::string CN;

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
  void Skills();

  void CharName();
  void PlayerName();

  void printChar(RandomSetUp& WOW);
  void fullrandom(RandomSetUp& WOW);
};