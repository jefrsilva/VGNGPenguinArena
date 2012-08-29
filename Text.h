#ifndef INC_TEXT_H
#define INC_TEXT_H

#include <string>

#include "SDL/SDL.h"

using namespace std;

const int ALIGN_LEFT   = 0;
const int ALIGN_CENTER = 1;
const int ALIGN_RIGHT  = 2;

class Text {
 private:
  SDL_Surface *screen;
  SDL_Surface *font;
  int x, y;
  int align;
  
 public:
  Text(SDL_Surface *screen, SDL_Surface *font, int x, int y, int align);
  ~Text();

  string text;

  void render();
};

#endif
