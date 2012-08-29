#ifndef INC_PENGUIN_H
#define INC_PENGUIN_H

#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "GlobalSettings.h"
#include "Object.h"
#include "Arena.h"
#include "WaterFX.h"
#include "ChallengeStats.h"

const int DIR_UP    = 1;
const int DIR_RIGHT = 2;
const int DIR_DOWN  = 4;
const int DIR_LEFT  = 8;
const int DIR_DASH  = 16; 

const int BOUNCE_STAMINA_REDUCTION = 10;

const int ITEM_DURATION = 900;

const int walkingFrames[] = {2, 1, 2, 3};

using namespace std;

class Penguin : public Object {
 protected:
  SDL_Surface *screen;
  SDL_Surface *penguin;
  Arena *map;
  Mix_Chunk *splash;
  Mix_Chunk *scream;

  bool dead;

  double frame;
  bool walking;
  bool bouncing;
  bool jumping;
  bool dying;
  double dyingCounter;

  int wonChallengeCounter;

  list<Object *> *effects;

 public:
  SDLKey cmd_up, cmd_right, cmd_down, cmd_left, cmd_dash;
  int playerNumber;
  bool slipping;
  int dashDistance;
  int dashDuration;
  int stamina;
  unsigned int dir;
  int score;
  int tmpScore;
  int scoreCounter;

  int currentItem;
  int powerupDuration;

  ChallengeStats *stats;

  int ax, ay;

  unsigned int keystate;

  Penguin();
  Penguin(SDL_Surface *screen, SDL_Surface *image, Arena *map, Mix_Chunk *splash, Mix_Chunk *scream, list<Object *> *effects);
  ~Penguin();

  virtual bool isDead();
  virtual void update();
  virtual void render(int flag);

  virtual CollisionBox getCollisionBox();

  virtual bool isPenguin();
  virtual void bounce(int dir, int type);
  virtual void die();

  virtual void addStamina(int qty);
  virtual void addScore(int qty);

  void wonChallenge();
};

#endif

