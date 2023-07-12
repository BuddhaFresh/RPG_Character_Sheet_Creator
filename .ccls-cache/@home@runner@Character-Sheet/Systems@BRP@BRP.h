#pragma once
#include "../../diceroller.h"

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
  std::string DamageBonus(); //change this to void
  int HitPoints();
  int MajorWounds();
  std::string DistinctiveFeatures();
  int ProSkillPointsPool();
  int PerSkillPonitsPool();

  void CharName();
  void PlayerName();


  void fullrandom();
  };