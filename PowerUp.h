#ifndef INC_POWERUP_H
#define INC_POWERUP_H

#include "SDL/SDL.h"

#include "GlobalSettings.h"
#include "Object.h"
#include "Item.h"
#include "Arena.h"
#include "Penguin.h"

class PowerUp : public Item {
 private:
  SDL_Surface *screen;
  SDL_Surface *powerup;
  Arena *arena;

  double frame;
  int type;

  bool dead;

  int expireTimer;

 public:
  PowerUp(SDL_Surface *screen, SDL_Surface *image, Arena *arena);
  ~PowerUp();

  bool isDead();
  void update();
  void render(int flag);

  CollisionBox getCollisionBox();

  void giveEffect(Penguin *penguin);
};

#endif
