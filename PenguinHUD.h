#ifndef INC_PENGUINHUD_H
#define INC_PENGUINHUD_H

#include <sstream>

#include "SDL/SDL.h"

#include "Penguin.h"
#include "Text.h"
#include "PowerUp.h"

using namespace std;

class PenguinHUD {
 private:
  SDL_Surface *screen;
  SDL_Surface *hud;
  SDL_Surface *font;
  Penguin *penguin;
  Text *heading;
  Text *text;
  Text *item;

 public:
  double x, y;

  PenguinHUD(SDL_Surface *screen, SDL_Surface *image, Penguin *penguin, SDL_Surface *font, int x, int y);
  ~PenguinHUD();

  void render();
  void die();
};

#endif
