#include "WaterFX.h"

WaterFX::WaterFX(SDL_Surface *screen, double x, double y) {
  this->screen = screen;

  this->x = x;
  this->y = y;
  this->z = 0;

  this->vx = (((double)rand() / (double)RAND_MAX) * 1.5) - 0.75;
  this->vy = (((double)rand() / (double)RAND_MAX) * 1.5) - 0.75;	
  this->vz = (((double)rand() / (double)RAND_MAX) * 2.0) + 2.0;
  
  this->dead = false;
}

WaterFX::~WaterFX() {
  
}

bool WaterFX::isDead() {
  return dead;
}

void WaterFX::update() {
  x += vx;
  y += vy;

  vz -= GRAVITY_ACCEL;
  if (vz < -5.0) {
    vz = -5.0;
  }
  z += vz;
  if (z <= 0.0) {
    dead = true;
  }
}

void WaterFX::render(int flag) {
  SDL_Rect dest;
  dest.x = (int)x;
  dest.y = (int)y;
  dest.w = 1;
  dest.h = 1;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));

  dest.x = (int)x;
  dest.y = (int)y - (int)z;
  if (vz > 0) {
    dest.w = 2;
    dest.h = 2;
  }
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 255, 255, 255));
}

CollisionBox WaterFX::getCollisionBox() {
  CollisionBox box;
  box.x = (int)x;
  box.y = (int)y;
  box.w = 1;
  box.h = 1;
  return box;
}
