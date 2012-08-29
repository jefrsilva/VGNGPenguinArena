#ifndef INC_FISH_H
#define INC_FISH_H

#include "SDL/SDL.h"

#include "Object.h"
#include "Item.h"
#include "Arena.h"
#include "Penguin.h"

const int fishAnimation[] = {0, 1, 0, 2};
const double SUPERFISH_CHANCE = 0.25;
const double ROTTENFISH_CHANCE = 0.1;

const int SCORE_FISH = 10;
const int SCORE_SUPERFISH = 30;

class Fish : public Item {
 private:
  SDL_Surface *screen;
  SDL_Surface *fish;
  Arena *arena;

  double frame;
  int jumpCounter;

  bool dead;

 public:
  Fish(SDL_Surface *screen, SDL_Surface *image, Arena *arena);
  ~Fish();

  int type;

  bool isDead();
  void update();
  void render(int flag);

  CollisionBox getCollisionBox();

  bool isFish();

  void giveEffect(Penguin *penguin);
};

#endif
