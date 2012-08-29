#ifndef INC_SEAL_H
#define INC_SEAL_H

#include "SDL/SDL.h"

#include "Object.h"
#include "Arena.h"

const int animation[] = {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0};

class Seal : public Object {
 private:
  bool dead;
  int swimCounter;
  Arena *arena;

 public:
  SDL_Surface *screen;
  SDL_Surface *seal;

  double frame;

  Seal(SDL_Surface *screen, SDL_Surface *image, Arena *arena);
  ~Seal();

  bool isDead();
  void update();
  void render(int flag);

  CollisionBox getCollisionBox();
  bool isSeal();
};

#endif
