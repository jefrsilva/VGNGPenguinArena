#include "Text.h"

Text::Text(SDL_Surface *screen, SDL_Surface *font, int x, int y, int align) {
  this->screen = screen;
  this->font = font;
  this->x = x;
  this->y = y;
  this->align = align;
}

Text::~Text() {
  
}

void Text::render() {
  SDL_Rect src;
  src.w = 7;
  src.h = 9;

  SDL_Rect dest;
  dest.w = 7;
  dest.h = 9;

  if (align == ALIGN_LEFT) {
    for (unsigned int i = 0; i < text.length(); i++) {
      src.x = (text[i] % 16) * 7;
      src.y = (text[i] / 16) * 9;
      dest.x = x + (i * 6);
      dest.y = y;
      SDL_BlitSurface(font, &src, screen, &dest);
    }
  } else if (align == ALIGN_CENTER) {
    for (unsigned int i = 0; i < text.length(); i++) {
      src.x = (text[i] % 16) * 7;
      src.y = (text[i] / 16) * 9;
      dest.x = x + (i * 6) - ((text.length() * 6) / 2);
      dest.y = y;
      SDL_BlitSurface(font, &src, screen, &dest);
    }    
  } else if (align == ALIGN_RIGHT) {
    for (unsigned int i = 0; i < text.length(); i++) {
      src.x = (text[i] % 16) * 7;
      src.y = (text[i] / 16) * 9;
      dest.x = x + (i * 6) - (text.length() * 6);
      dest.y = y;
      SDL_BlitSurface(font, &src, screen, &dest);
    }
  }
}
