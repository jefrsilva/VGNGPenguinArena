#ifndef INC_CHALLENGESTATS_H
#define INC_CHALLENGESTATS_H

#include <string>

#include "GlobalSettings.h"

using namespace std;

class ChallengeStats {
 private:
  bool ignore;

 public:
  ChallengeStats(string goal, int reward, int duration, bool checkOnExpire);
  ChallengeStats(bool ignore);
  ~ChallengeStats();

  string goal;
  int reward;
  int duration;
  bool checkOnExpire;
  
  int totalFishesCaught;
  int fishesCaught;
  int superFishesCaught;
  int rottenFishesCaught;
  int powerupsCaught;
  int scoreEarned;
  int timesBounced;
  int timesGotBounced;
  int timesWonSlide;
  int timesDrawSlide;
  int timesLostSlide;
  int timeNotMovingOnIce;
  int timeNotMovingOnWater;
  int timeOnWater;
  int timeOnIce;
  int timesFullDistanceSlide;

  void reset();

  void notify(int type);
  void notifyScore(int qty);
};

#endif
