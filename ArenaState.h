#ifndef INC_ARENASTATE_H
#define INC_ARENASTATE_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include <list>

#include "GlobalSettings.h"
#include "GameState.h"
#include "HighScoresState.h"
#include "Object.h"
#include "Item.h"
#include "Seal.h"
#include "Fish.h"
#include "PowerUp.h"
#include "Penguin.h"
#include "FishEater.h"
#include "Arena.h"
#include "PenguinHUD.h"
#include "ChallengeGenerator.h"

using namespace std;

const int MAX_PLAYERS = 4;
const int SEAL_INTERVAL = 600;
const int FISH_INTERVAL = 30;
const int EATER_INTERVAL = 180;
const int POWERUP_INTERVAL = 450;

const int SCORE_HIT = 5;

class ArenaState : public GameState {
 private:
  SDL_Surface *screen;
  SDL_Surface *penguin;
  SDL_Surface *seal;
  SDL_Surface *fish;
  SDL_Surface *interface;
  SDL_Surface *font;
  SDL_Surface *powerups;

  Mix_Chunk *squeak;
  Mix_Chunk *splash;
  Mix_Chunk *scream;
  Mix_Chunk *sip;
  Mix_Chunk *yeah;
  Mix_Chunk *metal;

  Mix_Music *music;

  HighScoresState *highscoreState;

  ChallengeGenerator *generator;

  list<Object *> objects;
  list<Object *> effects;
  Penguin *players[MAX_PLAYERS];
  PenguinHUD *huds[MAX_PLAYERS];

  int numPlayers;
  int numSeals;

  int sealCounter;
  int fishCounter;
  int eaterCounter;
  int powerupCounter;

  Arena *arena;

  bool gameover;

  double fade;
  double vfade;
  double afade;
  bool fadingIn;
  bool fadingOut;

 public:
  ArenaState(SDL_Surface *screen, int numPlayers);
  ~ArenaState();

  void handleKeyboardEvents(SDL_Event *event);
  void update();
  void render();

  void handleCollisions();
  void handlePenguinCommands(Penguin *penguin, SDL_Event *event);

  void playSound(int soundID);
};

#endif

