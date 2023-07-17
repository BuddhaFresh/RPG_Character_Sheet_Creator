#pragma once
#include "../../diceroller.h"
#include "../../menus.h"

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
  std::string PN;
  std::string CN;

  int CharacteristicRoll(int r);
  int Age();
  std::string DamageBonus();
  int HitPoints();
  int MajorWounds();
  std::string DistinctiveFeatures();
  int ProSkillPointsPool();
  int PerSkillPonitsPool();

  void CharName();
  void PlayerName();

  void printChar();
  void fullrandom(RandomSetUp& WOW);
  };