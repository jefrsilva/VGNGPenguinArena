#include "ChallengeStats.h"

ChallengeStats::ChallengeStats(string goal, int reward, int duration, bool checkOnExpire) {
  this->ignore = false;

  this->goal = goal;
  this->reward = reward;
  this->duration = duration;
  this->checkOnExpire = checkOnExpire;

  totalFishesCaught = 0;
  fishesCaught = 0;
  superFishesCaught = 0;
  rottenFishesCaught = 0;
  powerupsCaught = 0;
  scoreEarned = 0;
  timesBounced = 0;
  timesGotBounced = 0;
  timesWonSlide = 0;
  timesDrawSlide = 0;
  timesLostSlide = 0;
  timeNotMovingOnIce = 0;
  timeNotMovingOnWater = 0;
  timeOnWater = 0;
  timeOnIce = 0;
  timesFullDistanceSlide = 0;
}

ChallengeStats::ChallengeStats(bool ignore) {
  this->ignore = ignore;
  
  this->goal = "";
  this->reward = 0;
  
  totalFishesCaught = 0;
  fishesCaught = 0;
  superFishesCaught = 0;
  rottenFishesCaught = 0;
  powerupsCaught = 0;
  scoreEarned = 0;
  timesBounced = 0;
  timesGotBounced = 0;
  timesWonSlide = 0;
  timesDrawSlide = 0;
  timesLostSlide = 0;
  timeNotMovingOnIce = 0;
  timeNotMovingOnWater = 0;
  timeOnIce = 0;
  timeOnWater = 0;
  timesFullDistanceSlide = 0;
}

ChallengeStats::~ChallengeStats() {

}

void ChallengeStats::reset() {
  totalFishesCaught = 0;
  fishesCaught = 0;
  superFishesCaught = 0;
  rottenFishesCaught = 0;
  powerupsCaught = 0;
  scoreEarned = 0;
  timesBounced = 0;
  timesGotBounced = 0;
  timesWonSlide = 0;
  timesDrawSlide = 0;
  timesLostSlide = 0;
  timeNotMovingOnIce = 0;
  timeNotMovingOnWater = 0;
  timeOnIce = 0;
  timeOnWater = 0;
  timesFullDistanceSlide = 0;
}

void ChallengeStats::notify(int type) {
  if (ignore) {
    return;
  }

  switch (type) {
  case NOTIFY_GETPOWERUP:
    powerupsCaught++;
    break;

  case NOTIFY_GETFISH:
    fishesCaught++;
    totalFishesCaught++;
    break;

  case NOTIFY_GETSUPERFISH:
    superFishesCaught++;
    totalFishesCaught++;
    break;

  case NOTIFY_GETROTTENFISH:
    rottenFishesCaught++;
    totalFishesCaught++;
    break;
    
  case NOTIFY_BOUNCED:
    timesBounced++;
    break;

  case NOTIFY_GOTBOUNCED:
    timesGotBounced++;
    break;

  case NOTIFY_WONSLIDE:
    timesWonSlide++;
    break;

  case NOTIFY_DRAWSLIDE:
    timesDrawSlide++;
    break;

  case NOTIFY_LOSTSLIDE:
    timesLostSlide++;
    break;

  case NOTIFY_NOTMOVINGWATER:
    timeNotMovingOnWater++;
    break;

  case NOTIFY_MOVEDONWATER:
    timeNotMovingOnWater = 0;
    break;

  case NOTIFY_NOTMOVINGICE:
    timeNotMovingOnIce++;
    break;

  case NOTIFY_MOVEDONICE:
    timeNotMovingOnIce = 0;
    break;

  case NOTIFY_ENTEREDWATER:
    timeOnIce = 0;
    break;

  case NOTIFY_LEFTWATER:
    timeOnWater = 0;
    break;

  case NOTIFY_ONICE:
    timeOnIce++;
    break;

  case NOTIFY_ONWATER:
    timeOnWater++;
    break;

  case NOTIFY_FULLSLIDE:
    timesFullDistanceSlide++;
    break;
  }
}

void ChallengeStats::notifyScore(int qty) {
  if (ignore) {
    return;
  }

  scoreEarned += qty;
}

