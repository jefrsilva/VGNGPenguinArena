#ifndef INC_FISHEATER_H
#define INC_FISHEATER_H

#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "Object.h"
#include "Penguin.h"
#include "Arena.h"
#include "WaterFX.h"
#include "ChallengeGenerator.h"
#include "ChallengeStats.h"

const double ANGRYEATER_CHANCE = 0.65;
const double SUPEREATER_CHANCE = 0.20;

class FishEater : public Penguin {
 private:
  Arena *map;

  list<Object *> *objects;
  Object *target;

  int type;
  
 public:
  FishEater(SDL_Surface *screen, SDL_Surface *image, Arena *map, list<Object *> *objects, Mix_Chunk *splash, Mix_Chunk *scream, list<Object *> *effects, ChallengeGenerator *generator);
  ~FishEater();

  bool isDead();
  void update();

  void executeAI();
  void render(int flag);

  void addStamina(int qty);
  void addScore(int qty);
};

#endif

