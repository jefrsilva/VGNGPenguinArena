#ifndef INC_WATERFX_H
#define INC_WATERFX_H

#include "SDL/SDL.h"

#include "Object.h"
#include "Arena.h"

class WaterFX : public Object {
 private:
  SDL_Surface *screen;

  bool dead;

 public:
  WaterFX(SDL_Surface *screen, double x, double y);
  ~WaterFX();

  bool isDead();

  void update();
  void render(int flag);

  CollisionBox getCollisionBox();
};

#endif
