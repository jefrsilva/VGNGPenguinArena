#include "Seal.h"

Seal::Seal(SDL_Surface *screen, SDL_Surface *image, Arena *arena) {
  this->screen = screen;
  this->seal = image;
  this->arena = arena;

  this->dead = false;
  this->passable = false;

  this->frame = 0.0;

  this->x = rand() % (SCREEN_WIDTH - 32);
  this->y = rand() % (SCREEN_HEIGHT - 24);
  this->z = -6.0;

  this->vx = (((double)rand() / (double)RAND_MAX) * 2.0) - 1.0;
  this->vy = (((double)rand() / (double)RAND_MAX) * 2.0) - 1.0;	
  this->swimCounter = (rand() % 180) + 180;	
}

Seal::~Seal() {

}

bool Seal::isDead() {
  return dead;
}

void Seal::update() {
  if (swimCounter > 0) {
    x += vx;
    if (x < 16) {
      vx *= -1;
      x = 16;
    } 
    if (x > (SCREEN_WIDTH - 16)) {
      vx *= -1;
      x = SCREEN_WIDTH - 16;
    }
    y += vy;
    if (y < 12) {
      vy *= -1;
      y = 12;
    } 
    if (y > (SCREEN_HEIGHT - 12)) {
      vy *= -1;
      y = SCREEN_HEIGHT - 12;
    }    

    swimCounter--;
    if (swimCounter == 0) {
      frame = 0.0;

      int tmpx = ((int)x / 16) * 16;
      int tmpy = ((int)y / 12) * 12;
      
      int tileUL, tileUR, tileBL, tileBR;
      tileUL = arena->getTile(tmpx, tmpy);
      tileUR = arena->getTile(tmpx+16, tmpy);
      tileBL = arena->getTile(tmpx, tmpy+12);
      tileBR = arena->getTile(tmpx+16, tmpy+12);
      
      if (tileUL != TILE_WATER || tileUR != TILE_WATER ||
	  tileBL != TILE_WATER || tileBR != TILE_WATER) {
	swimCounter = 60;	
      } else {
	x = tmpx;
	y = tmpy;
      }
    }
  } else if (swimCounter == 0) {
    frame += 0.20;
    if (frame >= 12.0) {
      vx = (((double)rand() / (double)RAND_MAX) * 2.0) - 1.0;
      vy = (((double)rand() / (double)RAND_MAX) * 2.0) - 1.0;	
      swimCounter = (rand() % 180) + 180;	
    }
  }
}

void Seal::render(int flag) {
  SDL_Rect src;
  src.x = 96;
  src.y = 0;
  src.w = 32;
  src.h = 24;
  
  SDL_Rect dest;
  dest.x = (short)x;
  dest.y = (short)y;
  dest.w = 32;
  dest.h = 24;
  
  if (swimCounter == 0) {
    src.x = animation[(int)frame] * 32;
    if (vx > 0) {
      src.y = 0;
    } else {
      src.y = 24;
    }

    SDL_BlitSurface(seal, &src, screen, &dest);
  } else if (flag == 1) {
    SDL_BlitSurface(seal, &src, screen, &dest);
  }
}

CollisionBox Seal::getCollisionBox() {
  CollisionBox box;
  box.x = (int)x + 9;
  box.y = (int)y + 12;
  box.w = 15;
  box.h = 6;

  return box;
}

bool Seal::isSeal() {
  return true;
}
