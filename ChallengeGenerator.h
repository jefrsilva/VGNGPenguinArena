#ifndef INC_CHALLENGEGENERATOR_H
#define INC_CHALLENGEGENERATOR_H

#include <vector>
#include <sstream>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "Text.h"
#include "Penguin.h"
#include "ChallengeStats.h"

using namespace std;

class ChallengeGenerator {
 private:
  SDL_Surface *screen;
  SDL_Surface *font;

  Mix_Chunk *soundNewChallenge;
  Mix_Chunk *soundWonChallenge;

  vector<Penguin *> players;
  vector<ChallengeStats *> challenges;
  vector<ChallengeStats *> multiPlayerChallenges;

  int nextChallengeTimer;
  int expireChallengeTimer;
  int currentChallenge;
  
  double frame;

  Text *textGoal;
  Text *textInfo;

 public:
  ChallengeGenerator(SDL_Surface *screen, SDL_Surface *font);
  ~ChallengeGenerator();

  int numPlayers;
  bool multiChallenge;

  void registerPlayer(Penguin *penguin);

  void update();
  void render();
};

#endif
