#include "Fish.h"

Fish::Fish(SDL_Surface *screen, SDL_Surface *image, Arena *arena) {
  this->screen = screen;
  this->fish = image;
  this->arena = arena;

  this->passable = true;

  this->frame = 0.0;
  
  Position pos = this->arena->getRandomIceTile();
  this->x = (pos.x * 16) + 8;
  this->y = (pos.y * 12) + 6;
  this->z = SCREEN_HEIGHT;

  this->vx = 0.0;
  this->vy = 0.0;
  this->vz = 0.0;

  double chance = ((double)rand() / (double)RAND_MAX);
  if (chance < ROTTENFISH_CHANCE) {
    this->type = 2;
  } else if (chance < SUPERFISH_CHANCE) {
    this->type = 1;
  } else {
    this->type = 0;
  }

  if (pos.x < 0) {
    this->dead = true;
  } else {
    this->dead = false;
  }
  this->jumpCounter = 0;
}

Fish::~Fish() {

}

bool Fish::isDead() {
  return dead;
}

void Fish::update() {
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

  if (jumpCounter > 0) {
    jumpCounter--;
  }
  if (jumpCounter == 0 && z == 0.0) {
    jumpCounter = (rand() % 120) + 60;
    vz = (((double)rand() / (double)RAND_MAX) * 2.0) + 2.0;
    vx = (((double)rand() / (double)RAND_MAX) * 2.0) - 1.0;
    vy = (((double)rand() / (double)RAND_MAX) * 2.0) - 1.0;	
  }
}

void Fish::render(int flag) {
  SDL_Rect src;
  src.x = fishAnimation[(int)frame] * 8;
  src.y = type * 7;
  src.w = 8;
  src.h = 7;

  SDL_Rect dest;
  dest.x = (short)x - 4;
  dest.y = (short)y - short(z) - 4;
  dest.w = 8;
  dest.h = 7;

  SDL_BlitSurface(fish, &src, screen, &dest);

  if (z > 0.0) {
    src.x = 3 * 8;
    src.y = 0;
    dest.x = (short)x - 4;
    dest.y = (short)y - 4;
    SDL_BlitSurface(fish, &src, screen, &dest);
  }
}

CollisionBox Fish::getCollisionBox() {
  CollisionBox box;
  box.x = (short)x - 4;
  box.y = (short)y - 4;
  box.w = 8;
  box.h = 7;
  box.z = (short)z;
  box.zh = 0;

  return box;
}

bool Fish::isFish() {
  return true;
}

void Fish::giveEffect(Penguin *penguin) {
  if (this->type == 2) {
    penguin->addStamina(-50);
  } else if (this->type == 1) {
    penguin->addStamina(20);
    penguin->addScore(SCORE_SUPERFISH);
  } else {
    penguin->addStamina(5);
    penguin->addScore(SCORE_FISH);
  }
  dead = true;
}

