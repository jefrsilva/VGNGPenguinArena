#include "PowerUp.h"

PowerUp::PowerUp(SDL_Surface *screen, SDL_Surface *image, Arena *arena) {
  this->screen = screen;
  this->powerup = image;
  this->arena = arena;

  this->passable = true;

  this->frame = 0.0;
  
  Position pos = this->arena->getRandomIceTile();
  this->x = pos.x * 16;
  this->y = (pos.y * 12) + 6;
  this->z = SCREEN_HEIGHT;

  this->vx = 0.0;
  this->vy = 0.0;
  this->vz = 0.0;

  this->type = (rand() % 5) + 1;

  if (pos.x < 0) {
    this->dead = true;
  } else {
    this->dead = false;
  }

  this->expireTimer = 900;
}

PowerUp::~PowerUp() {

}

bool PowerUp::isDead() {
  return dead;
}

void PowerUp::update() {
  expireTimer--;
  if (expireTimer <= 0) {
    dead = true;
    return;
  }

  double zlimit = 0.0;
  if (arena->getTile(x, y) == TILE_WATER) {
    zlimit = -6.0;
    if (z == zlimit) {
      dead = true;
    }
  }

  x += vx;
  if (x < 0) {
    x = 0;
  }
  if (x > SCREEN_WIDTH) {
    x = SCREEN_WIDTH;
  }
  y += vy;
  if (y < 0) {
    y = 0;
  }
  if (y > SCREEN_HEIGHT) {
    y = SCREEN_HEIGHT;
  }
  
  vz -= GRAVITY_ACCEL;
  if (vz < -5.0) {
    vz = -5.0;
  }
  z += vz;
  if (z < zlimit && vz < 0.0) {
    z = zlimit;
  }

  frame += 0.25;
  if (frame >= 4.0) {
    frame = 0.0;
  }
}

void PowerUp::render(int flag) {
  if (expireTimer < 300) {
    if ((int)frame % 2 == 0) {
      return;
    }
  }

  SDL_Rect src;
  SDL_Rect dest;

  src.x = 4 * 16;
  src.y = 0;
  src.w = 16;
  src.h = 16;
  dest.x = (short)x;
  dest.y = (short)y - 14;
  dest.w = 16;
  dest.h = 16;
  SDL_BlitSurface(powerup, &src, screen, &dest);

  if (type == POWERUP_CONFUSION) {
    src.x = (int)frame * 16;
  } else {
    src.x = (type - 1) * 16;
  }
  src.y = 0;
  src.w = 16;
  src.h = 16;

  dest.x = (short)x;
  dest.y = (short)y - short(z) - 16;
  dest.w = 16;
  dest.h = 16;
  SDL_BlitSurface(powerup, &src, screen, &dest);

}

CollisionBox PowerUp::getCollisionBox() {
  CollisionBox box;
  box.x = (short)x + 1;
  box.y = (short)y - 4;
  box.w = 14;
  box.h = 7;
  box.z = (short)z;
  box.zh = 0;

  return box;
}

void PowerUp::giveEffect(Penguin *penguin) {
  if (this->type == POWERUP_CONFUSION) {
    this->type = (rand() % 5) + 1;
  }

  if (this->type == POWERUP_POWER) {
    penguin->currentItem = this->type;
    penguin->powerupDuration = ITEM_DURATION;
  } else if (this->type == POWERUP_STONE) {
    penguin->currentItem = this->type;
    penguin->powerupDuration = ITEM_DURATION;
  } else if (this->type == POWERUP_DASH) {
    penguin->currentItem = this->type;
    penguin->powerupDuration = ITEM_DURATION;
  } else if (this->type == POWERUP_SPEED) {
    penguin->currentItem = this->type;
    penguin->powerupDuration = ITEM_DURATION;
  } else if (this->type == POWERUP_CONFUSION) {
    penguin->currentItem = this->type;
    penguin->powerupDuration = ITEM_DURATION;
  }
  dead = true;
}

