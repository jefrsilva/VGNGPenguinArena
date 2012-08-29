#include "ChallengeGenerator.h"

#include <iostream>

using namespace std;

bool cmpStats(const ChallengeStats *a,
	      const ChallengeStats *b) {
  bool lessThan = false;

  if (a->powerupsCaught < b->powerupsCaught) {
    lessThan = true;
  }
  if (a->totalFishesCaught < b->totalFishesCaught) {
    lessThan = true;
  }
  if (a->fishesCaught < b->fishesCaught) {
    lessThan = true;
  }
  if (a->superFishesCaught < b->superFishesCaught) {
    lessThan = true;
  }
  if (a->rottenFishesCaught < b->rottenFishesCaught) {
    lessThan = true;
  }
  if (a->timesBounced < b->timesBounced) {
    lessThan = true;
  }
  if (a->timesGotBounced < b->timesGotBounced) {
    lessThan = true;
  }
  if (a->timesWonSlide < b->timesWonSlide) {
    lessThan = true;
  }
  if (a->timesDrawSlide < b->timesDrawSlide) {
    lessThan = true;
  }
  if (a->timesLostSlide < b->timesLostSlide) {
    lessThan = true;
  }
  if (a->scoreEarned < b->scoreEarned) {
    lessThan = true;
  }
  if (a->timeNotMovingOnIce < b->timeNotMovingOnIce) {
    lessThan = true;
  }
  if (a->timeNotMovingOnWater < b->timeNotMovingOnWater) {
    lessThan = true;
  }
  if (a->timeOnWater < b->timeOnWater) {
    lessThan = true;
  }
  if (a->timeOnIce < b->timeOnIce) {
    lessThan = true;
  }
  if (a->timesFullDistanceSlide < b->timesFullDistanceSlide) {
    lessThan = true;
  }

  return lessThan;
}

bool cmpStatsMulti(const ChallengeStats *r, 
		   const ChallengeStats *a, const ChallengeStats *b) {
  if (r->powerupsCaught) {
    return a->powerupsCaught > b->powerupsCaught;
  }
  if (r->totalFishesCaught) {
    return a->totalFishesCaught > b->totalFishesCaught;
  }
  if (r->fishesCaught) {
    return a->fishesCaught > b->fishesCaught;
  }
  if (r->superFishesCaught) {
    return a->superFishesCaught > b->superFishesCaught;
  }
  if (r->rottenFishesCaught) {
    return a->rottenFishesCaught > b->rottenFishesCaught;
  }
  if (r->timesBounced) {
    return a->timesBounced > b->timesBounced;
  }
  if (r->timesGotBounced) {
    return a->timesGotBounced > b->timesGotBounced;
  }
  if (r->timesWonSlide) {
    return a->timesWonSlide > b->timesWonSlide;
  }
  if (r->timesDrawSlide) {
    return a->timesDrawSlide > b->timesDrawSlide;
  }
  if (r->timesLostSlide) {
    return a->timesLostSlide > b->timesLostSlide;
  }
  if (r->scoreEarned) {
    return a->scoreEarned > b->scoreEarned;
  }
  if (r->timeNotMovingOnIce) {
    return a->timeNotMovingOnIce > b->timeNotMovingOnIce;
  }
  if (r->timeNotMovingOnWater) {
    return a->timeNotMovingOnWater > b->timeNotMovingOnWater;
  }
  if (r->timeOnWater) {
    return a->timeOnWater > b->timeOnWater;
  }
  if (r->timeOnIce) {
    return a->timeOnIce > b->timeOnIce;
  }
  if (r->timesFullDistanceSlide) {
    return a->timesFullDistanceSlide > b->timesFullDistanceSlide;
  }

  return false;
}

bool cmpStatsMultiEqual(const ChallengeStats *r, 
		   const ChallengeStats *a, const ChallengeStats *b) {
  if (r->powerupsCaught) {
    return a->powerupsCaught == b->powerupsCaught;
  }
  if (r->totalFishesCaught) {
    return a->totalFishesCaught == b->totalFishesCaught;
  }
  if (r->fishesCaught) {
    return a->fishesCaught == b->fishesCaught;
  }
  if (r->superFishesCaught) {
    return a->superFishesCaught == b->superFishesCaught;
  }
  if (r->rottenFishesCaught) {
    return a->rottenFishesCaught == b->rottenFishesCaught;
  }
  if (r->timesBounced) {
    return a->timesBounced == b->timesBounced;
  }
  if (r->timesGotBounced) {
    return a->timesGotBounced == b->timesGotBounced;
  }
  if (r->timesWonSlide) {
    return a->timesWonSlide == b->timesWonSlide;
  }
  if (r->timesDrawSlide) {
    return a->timesDrawSlide == b->timesDrawSlide;
  }
  if (r->timesLostSlide) {
    return a->timesLostSlide == b->timesLostSlide;
  }
  if (r->scoreEarned) {
    return a->scoreEarned == b->scoreEarned;
  }
  if (r->timeNotMovingOnIce) {
    return a->timeNotMovingOnIce == b->timeNotMovingOnIce;
  }
  if (r->timeNotMovingOnWater) {
    return a->timeNotMovingOnWater == b->timeNotMovingOnWater;
  }
  if (r->timeOnWater) {
    return a->timeOnWater == b->timeOnWater;
  }
  if (r->timeOnIce) {
    return a->timeOnIce == b->timeOnIce;
  }
  if (r->timesFullDistanceSlide) {
    return a->timesFullDistanceSlide == b->timesFullDistanceSlide;
  }

  return false;
}

ChallengeGenerator::ChallengeGenerator(SDL_Surface *screen, SDL_Surface *font) {
  this->screen = screen;
  this->font = font;

  this->soundNewChallenge = Mix_LoadWAV("newchallenge.ogg");
  this->soundWonChallenge = Mix_LoadWAV("wonchallenge.ogg");

  this->currentChallenge = -1;
  this->nextChallengeTimer = CHALLENGE_NEXT_INTERVAL;
  this->expireChallengeTimer = 0;

  this->frame = 0.0;

  this->multiChallenge = false;

  ChallengeStats *newChallenge;

  newChallenge = new ChallengeStats("GET 1 FISH", 50, 900, false);
  newChallenge->totalFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET 3 FISHES", 100, 1800, false);
  newChallenge->totalFishesCaught = 3;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET 5 FISHES", 150, 3600, false);
  newChallenge->totalFishesCaught = 5;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET 1 RED FISH AND 1 GREEN FISH", 100, 1800, false);
  newChallenge->fishesCaught = 1;
  newChallenge->superFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET 1 RED FISH AND 1 BLACK FISH", 100, 1800, false);
  newChallenge->fishesCaught = 1;
  newChallenge->rottenFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET 1 GREEN FISH AND 1 BLACK FISH", 100, 1800, false);
  newChallenge->superFishesCaught = 1;
  newChallenge->rottenFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET A RED FISH", 50, 600, false);
  newChallenge->fishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET A GREEN FISH", 100, 1200, false);
  newChallenge->superFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET A BLACK FISH", 150, 1800, false);
  newChallenge->rottenFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET 1 FISH OF EACH KIND", 200, 3600, false);
  newChallenge->fishesCaught = 1;
  newChallenge->superFishesCaught = 1;
  newChallenge->rottenFishesCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET BOUNCED 3 TIMES", 100, 1800, false);
  newChallenge->timesGotBounced = 3;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("BOUNCE 1 PENGUIN", 50, 600, false);
  newChallenge->timesBounced = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("BOUNCE 3 PENGUINS", 100, 1200, false);
  newChallenge->timesBounced = 3;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("BOUNCE 5 PENGUINS", 150, 1800, false);
  newChallenge->timesBounced = 5;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("SCORE 50 POINTS", 50, 900, false);
  newChallenge->scoreEarned = 50;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("SCORE 150 POINTS", 150, 1800, false);
  newChallenge->scoreEarned = 150;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("STAY ON THE WATER WITHOUT MOVING FOR 5 SECONDS", 200, 1800, false);
  newChallenge->timeNotMovingOnWater = 300;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("STAY ON THE WATER FOR 15 SECONDS", 200, 1800, false);
  newChallenge->timeOnWater = 900;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("STAY ON THE ICE WITHOUT MOVING FOR 5 SECONDS", 100, 1800, false);
  newChallenge->timeNotMovingOnIce = 300;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("STAY ON THE ICE FOR 15 SECONDS", 100, 1800, false);
  newChallenge->timeOnIce = 900;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("PERFORM 3 FULL DISTANCE SLIDES", 100, 1800, false);
  newChallenge->timesFullDistanceSlide = 3;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET A POWERUP", 50, 900, false);
  newChallenge->powerupsCaught = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("WIN A SLIDING DUEL", 100, 1800, false);
  newChallenge->timesWonSlide = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("LOSE A SLIDING DUEL", 100, 1800, false);
  newChallenge->timesLostSlide = 1;
  challenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("DRAW A SLIDING DUEL", 200, 1800, false);
  newChallenge->timesDrawSlide = 1;
  challenges.push_back(newChallenge);



  newChallenge = new ChallengeStats("GET MORE FISHES THAN YOUR OPPONENTS", 100, 1800, true);
  newChallenge->totalFishesCaught = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET MORE RED FISHES THAN YOUR OPPONENTS", 200, 1800, true);
  newChallenge->fishesCaught = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET MORE GREEN FISHES THAN YOUR OPPONENTS", 200, 1800, true);
  newChallenge->superFishesCaught = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET MORE BLACK FISHES THAN YOUR OPPONENTS", 200, 1800, true);
  newChallenge->rottenFishesCaught = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("BOUNCE MORE PENGUINS THAN YOUR OPPONENTS", 150, 1800, true);
  newChallenge->timesBounced = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("GET BOUNCED MORE TIMES THAN YOUR OPPONENTS", 150, 1800, true);
  newChallenge->timesGotBounced = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("SCORE MORE POINTS THAN YOUR OPPONENTS", 100, 1800, true);
  newChallenge->scoreEarned = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("STAY ON THE WATER LONGER THAN YOUR OPPONENTS", 200, 1800, true);
  newChallenge->timeOnWater = 1;
  multiPlayerChallenges.push_back(newChallenge);

  newChallenge = new ChallengeStats("STAY ON THE ICE LONGER THAN YOUR OPPONENTS", 200, 1800, true);
  newChallenge->timeOnIce = 1;
  multiPlayerChallenges.push_back(newChallenge);

  textGoal = new Text(screen, font, 320, 456, ALIGN_CENTER);
  textInfo = new Text(screen, font, 320, 468, ALIGN_CENTER);
}

ChallengeGenerator::~ChallengeGenerator() {
  delete textGoal;
  delete textInfo;

  Mix_FreeChunk(soundNewChallenge);
  Mix_FreeChunk(soundWonChallenge);

  for (unsigned int i = 0; i < challenges.size(); i++) {
    delete challenges[i];
  }
}

void ChallengeGenerator::registerPlayer(Penguin *penguin) {
  players.push_back(penguin);
}

void ChallengeGenerator::update() {
  frame += 0.25;

  if (currentChallenge == -1) {
    nextChallengeTimer--;

    if (nextChallengeTimer <= 0) {
      nextChallengeTimer = 0;
      double type = ((double)rand() / (double)RAND_MAX);
      
      if (numPlayers > 1 && multiPlayerChallenges.size() && type >= 0.5) {
        currentChallenge = rand() % multiPlayerChallenges.size();
	expireChallengeTimer = 
	  multiPlayerChallenges[currentChallenge]->duration;
	multiChallenge = true;
	
	for (unsigned int i = 0; i < players.size(); i++) {
	  players[i]->stats->reset();
	}

	Mix_PlayChannel(-1, soundNewChallenge, 0); 
      } else {
	if (challenges.size()) {
	  currentChallenge = rand() % challenges.size();
	  expireChallengeTimer = challenges[currentChallenge]->duration;
	  multiChallenge = false;
	  
	  for (unsigned int i = 0; i < players.size(); i++) {
	    players[i]->stats->reset();
	  }
	  
	  Mix_PlayChannel(-1, soundNewChallenge, 0); 
	}
      }
    }
	
    return;
  }

  vector<Penguin *> winners;
  
  expireChallengeTimer--;
  if (expireChallengeTimer <= 0) {
    expireChallengeTimer = 0;

    nextChallengeTimer = CHALLENGE_NEXT_INTERVAL;

    if (!multiChallenge) {
      ChallengeStats *challenge = challenges[currentChallenge];
      challenges.erase(challenges.begin() + currentChallenge);
      delete challenge;
      currentChallenge = -1;

      multiChallenge = false;
      return;
    } else {
      Penguin *tmp;
      vector<Penguin *> tmpPlayers;
      for (unsigned int i = 0; i < players.size(); i++) {
	if (!players[i]->isDead()) {
	  tmpPlayers.push_back(players[i]);
	}
      }

      for (unsigned int i = 0; i < tmpPlayers.size(); i++) {
	for (unsigned int j = 0; j < tmpPlayers.size() - 1; j++) {
	  if (cmpStatsMulti(multiPlayerChallenges[currentChallenge], 
			     tmpPlayers[j+1]->stats, tmpPlayers[j]->stats)) {
	    tmp = tmpPlayers[j+1];
	    tmpPlayers[j+1] = tmpPlayers[j];
	    tmpPlayers[j] = tmp;
	  }
	}
      }

      unsigned int i = 0;
      while (i < tmpPlayers.size() - 1 &&
	     cmpStatsMultiEqual(multiPlayerChallenges[currentChallenge], 
				tmpPlayers[i]->stats, tmpPlayers[i+1]->stats)) {
	winners.push_back(tmpPlayers[i]);
	i++;
      }
      winners.push_back(tmpPlayers[i]);
    }
  }

  if (!multiChallenge) {
    for (unsigned int i = 0; i < players.size(); i++) {
      if (!players[i]->isDead()) {
	if (!(cmpStats(players[i]->stats, challenges[currentChallenge]))) {
	  winners.push_back(players[i]);
	}
      }
    }
  }

  if (winners.size()) {
    nextChallengeTimer = CHALLENGE_NEXT_INTERVAL;
    int reward = 0;
    
    if (multiChallenge) {
      reward = multiPlayerChallenges[currentChallenge]->reward;
      ChallengeStats *challenge = multiPlayerChallenges[currentChallenge];
      multiPlayerChallenges.erase(multiPlayerChallenges.begin() + currentChallenge);
      delete challenge;
    } else {
      reward = challenges[currentChallenge]->reward;
      ChallengeStats *challenge = challenges[currentChallenge];
      challenges.erase(challenges.begin() + currentChallenge);
      delete challenge;
    }
    currentChallenge = -1;

    for (unsigned int i = 0; i < winners.size(); i++) {
      winners[i]->addScore(reward);
      winners[i]->wonChallenge();
    }

    Mix_PlayChannel(-1, soundWonChallenge, 0);     
  }
}

void ChallengeGenerator::render() {
  if (currentChallenge == -1) {
    return;
  }

  if (!multiChallenge) {
    if (challenges[currentChallenge]->duration - expireChallengeTimer <= 120) {
      if ((int)frame % 4 > 1) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 454;
	rect.w = 640;
	rect.h = 26;
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0));
      }
    }
  } else {
    if (multiPlayerChallenges[currentChallenge]->duration - expireChallengeTimer <= 120) {
      if ((int)frame % 4 > 1) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 454;
	rect.w = 640;
	rect.h = 26;
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 0));
      }
    }
  }

  if (!multiChallenge) {
    textGoal->text = challenges[currentChallenge]->goal;
    stringstream out;
    out << challenges[currentChallenge]->reward << " POINTS CHALLENGE : " <<
      (expireChallengeTimer / 60) << " SECONDS REMAINING";
    textInfo->text = out.str();
  } else {
    textGoal->text = multiPlayerChallenges[currentChallenge]->goal;
    stringstream out;
    out << multiPlayerChallenges[currentChallenge]->reward << " POINTS CHALLENGE : " <<
      (expireChallengeTimer / 60) << " SECONDS REMAINING";
    textInfo->text = out.str();
  }
  
  if (expireChallengeTimer <= 300) {
    if ((int)frame % 2 == 0) {
      textGoal->render();
      textInfo->render();
    }
  } else {
    textGoal->render();
    textInfo->render();
  }
}




