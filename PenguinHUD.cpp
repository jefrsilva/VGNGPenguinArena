#include "PenguinHUD.h"

PenguinHUD::PenguinHUD(SDL_Surface *screen, SDL_Surface *image, 
		       Penguin *penguin, SDL_Surface *font, int x, int y) {
  this->screen = screen;
  this->hud = image;
  this->penguin = penguin;
  this->font = font;
  this->x = x;
  this->y = y;
  this->heading = new Text(screen, font, x - 8, y + 4, ALIGN_RIGHT); 
  this->text = new Text(screen, font, x - 8, y + 15, ALIGN_RIGHT);
  this->item = new Text(screen, font, x + 7, y + 29, ALIGN_CENTER);
}

PenguinHUD::~PenguinHUD() {
  delete this->heading;
  delete this->text;
  delete this->item;
}

void PenguinHUD::render() {
  SDL_Rect src;
  SDL_Rect dest;
  unsigned int color = SDL_MapRGB(screen->format, 0, 0, 0);
  unsigned int white = SDL_MapRGB(screen->format, 255, 255, 255);

  if (penguin->playerNumber == 1) {
    color = SDL_MapRGB(screen->format, 255, 0, 0);
  } else if (penguin->playerNumber == 2) {
    color = SDL_MapRGB(screen->format, 255, 255, 0);
  } else if (penguin->playerNumber == 3) {
    color = SDL_MapRGB(screen->format, 0, 255, 0);
  } else if (penguin->playerNumber == 4) {
    color = SDL_MapRGB(screen->format, 0, 96, 255);
  }

  dest.x = (short)x + 20;
  dest.y = (short)y + 9;
  dest.w = 29;
  dest.h = 4;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 64, 64, 64));
  dest.x = (short)x + 20;
  dest.y = (short)y + 9;
  dest.w = (short)(((double)penguin->stamina / 100.0) * (double)29);
  dest.h = 4;
  if (penguin->isDead()) {
    dest.w = 0;
  }
  SDL_FillRect(screen, &dest, color);

  if (penguin->dashDuration < 60) {
    color = white;
  }

  double slide = ((double)penguin->dashDuration);
  if (slide < 0.0) {
    slide = 0.0;
  }

  dest.x = (short)x + 20;
  dest.y = (short)y + 22;
  dest.w = 29;
  dest.h = 4;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 64, 64, 64));
  dest.x = (short)x + 20;
  dest.y = (short)y + 22;
  dest.w = (short)((slide / 120.0) * (double)29);
  dest.h = 4;
  if (penguin->isDead()) {
    dest.w = 0;
  }
  SDL_FillRect(screen, &dest, color);

  src.x = (penguin->playerNumber - 1) * 54;
  src.y = 0;
  src.w = 54;
  src.h = 29;

  dest.x = (short)x;
  dest.y = (short)y;
  dest.w = 54;
  dest.h = 29;
  SDL_BlitSurface(hud, &src, screen, &dest);

  stringstream out;
  out << penguin->score;
  string output = out.str();

  heading->text = "SCORE";
  heading->render();

  text->text = output;
  text->render();

  out.str("");
  if (!penguin->isDead()) {
    if (penguin->currentItem == POWERUP_POWER) {
      out << "POWER SLIDE " << (penguin->powerupDuration / 60);
    } else if (penguin->currentItem == POWERUP_STONE) {
      out << "IRON PENGUIN " << (penguin->powerupDuration / 60);
    } else if (penguin->currentItem == POWERUP_DASH) {
      out << "QUICK SLIDE " << (penguin->powerupDuration / 60);
    } else if (penguin->currentItem == POWERUP_SPEED) {
      out << "DOUBLE SPEED " << (penguin->powerupDuration / 60);
    } else if (penguin->currentItem == POWERUP_CONFUSION) {
      out << "CONFUSION " << (penguin->powerupDuration / 60);
    }
    item->text = out.str();
    item->render();
  }
}

void PenguinHUD::die() {

}
