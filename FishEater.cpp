#include "FishEater.h"

FishEater::FishEater(SDL_Surface *screen, SDL_Surface *image, Arena *map, list<Object *> *objects, Mix_Chunk *splash, Mix_Chunk *scream, list<Object*> *effects, ChallengeGenerator *generator) {
  this->screen = screen;
  this->penguin = image;
  this->map = map;
  this->objects = objects;
  this->splash = splash;
  this->scream = scream;
  
  this->dying = false;

  this->dir = 4;
  this->slipping = false;
  this->vx = 0.0;
  this->vy = 0.0;
  this->vz = 0.0;
  this->ax = 0;
  this->ay = 0;
  this->z = 0.0;
  
  this->keystate = 0;
  this->frame = 0.0;
  this->walking = false;
  this->bouncing = true;
  this->jumping = false;
  
  this->dashDuration = 120;
  this->dashDistance = 0;
  this->passable = false;

  Position pos = this->map->getRandomIceTile();
  this->x = (pos.x * 16) + 8;
  this->y = (pos.y * 12) + 6;
  this->z = SCREEN_HEIGHT;

  this->vx = 0.0;
  this->vy = 0.0;
  this->vz = 0.0;

  this->playerNumber = 0;
  this->target = 0;

  double chance = ((double)rand() / (double)RAND_MAX);
  if (chance < SUPEREATER_CHANCE) {
    this->stamina = 80;
    this->type = 2;
  } else if (chance < ANGRYEATER_CHANCE) {
    this->stamina = 0;
    this->type = 1;
  } else {
    this->stamina = 0;
    this->type = 0;
  }

  this->effects = effects;

  if (pos.x < 0) {
    this->dead = true;
  } else {
    this->dead = false;
  }

  this->currentItem = 0;
  this->powerupDuration = 0;

  this->stats = new ChallengeStats(true);
}

FishEater::~FishEater() {

}

bool FishEater::isDead() {
  return dead;
}

void FishEater::executeAI() {
  double distance = MAX_DISTANCE;

  list<Object *>::iterator it = objects->begin();
  while (it != objects->end()) {
    Object *obj = (*it);
    if (!obj->isDead()) {
      if (type != 2 && obj->isFish()) {
	double newDistance = distanceTo(*it);
	if (newDistance < distance) {
	  distance = newDistance;
	  target = obj;
	}
      }
      if (type > 0 && obj->isPenguin() && obj != this) {
	if (z < 0.0) {
	  if (((Penguin *)obj)->playerNumber > 0) {
	    double newDistance = distanceTo(*it);
	    if (newDistance < distance) {
	      distance = newDistance;
	      target = obj;
	    }      
	  }
	} else {
	  double newDistance = distanceTo(*it);
	  if (newDistance < distance) {
	    distance = newDistance;
	    target = obj;
	  }      
	}
      }
    }

    it++;
  }

  if (distance == MAX_DISTANCE) {
    target = 0;
  }
}

void FishEater::update() {
  if (dying) {
    frame = frame + 0.25;
    if (frame >= 2.0) {
      frame = 0.0;
    }
    dyingCounter -= 1.0;
    if (dyingCounter <= 0.0) {
      dead = true;
    }
    return;
  }
  
  double zlimit = 0.0;
  if (map->getTile(x, y) == TILE_WATER) {
    zlimit = -6.0;
  }

  vz -= GRAVITY_ACCEL;
  if (vz < -5.0) {
    vz = -5.0;
  }
  double lastz = z;
  z += vz;
  if (z < zlimit && vz < 0.0) {
    if (lastz > zlimit && z <= zlimit && zlimit == -6.0) {
      Mix_PlayChannel(-1, splash, 0); 

      for (int i = 0; i < 10; i++) {
	Object *fx = new WaterFX(screen, x, y);
	effects->push_back(fx);
      }
    }
    z = zlimit;
    bouncing = false;
    jumping = false;
  }

  executeAI();
  bool returnToArena = false;
  if (target) {
    keystate = 0;
    if (target->x > x + 4) {
      keystate = keystate | DIR_RIGHT;
    }
    if (target->x < x - 4) {
      keystate = keystate | DIR_LEFT;      
    }
    if (target->y > y - 4) {
      keystate = keystate | DIR_DOWN;
    }
    if (target->y < y + 4) {
      keystate = keystate | DIR_UP;      
    }
    if (distanceTo(target) > 8000) {
      keystate = keystate | DIR_DASH;            
    }
    if (type > 0 && target->isPenguin() && distanceTo(target) < 2000) {
      keystate = keystate | DIR_DASH;            
    }
    if (map->getTile(x, y) == TILE_WATER && 
	(x < 160 || x > 480 || y < 120 || y > 360)) {
      returnToArena = true;
    }
  }

  if (jumping) {
    x += vx * 0.35;
    y += vy * 0.7;
  } else if (!bouncing) {
    lastx = x;
    lasty = y;
    
    if (dashDuration <= 0) {
      slipping = false;
    }
    
    ax = ay = 0;
    if (keystate & DIR_UP) {
      ay--;
    }
    if (keystate & DIR_RIGHT) {
      ax++;
    }
    if (keystate & DIR_DOWN) {
      ay++;
    }
    if (keystate & DIR_LEFT) {
      ax--;
    }
    if (keystate & DIR_DASH && dashDuration >= 60 && z == 0) {
      slipping = true;
    }
    
    if (!slipping) {
      if (returnToArena) {
	if (x > 340) {
	  ax = -1;
	} else if (x < 300) {
	  ax = 1;
	} else {
	  ax = 0;
	}

	if (y > 260) {
	  ay = -1;
	} else if (y < 220) {
	  ay = 1;
	} else {
	  ay = 0;
	}
      }

      if (ay == -1 && ax == 0 && z == zlimit) {
	dir = 0;
      }
      if (ay == -1 && ax == 1 && z == zlimit) {
	dir = 1;
      }
      if (ay == 0 && ax == 1 && z == zlimit) {
	dir = 2;
      }
      if (ay == 1 && ax == 1 && z == zlimit) {
	dir = 3;
      }
      if (ay == 1 && ax == 0 && z == zlimit) {
	dir = 4;
      }
      if (ay == 1 && ax == -1 && z == zlimit) {
	dir = 5;
      }
      if (ay == 0 && ax == -1 && z == zlimit) {
	dir = 6;
      }
      if (ay == -1 && ax == -1 && z == zlimit) {
	dir = 7;
      }
      
      double waterSlow = 1.0;
      if (z == zlimit && z < 0.0) {
	waterSlow = (((double)stamina / 120.0) * 0.8) + 0.2;
      }

      double factor = 1.0;
      if (dir % 2 != 0) {
	factor = 0.7;
      }
      
      vx = ax * 1.0 * factor;
      vy = ay * 0.5 * factor;
      
      int lastTile = map->getTile(x, y);

      x += (vx * waterSlow);
      y += (vy * waterSlow);

      int curTile = map->getTile(x+4*vx, y+12*vy);

      if (lastTile != curTile) {
	slipping = false;
	jumping = true;
	vz = 1.5;
      }

      walking = ax || ay;
      if (walking) {
	frame += 0.10;
	if (frame >= 4.0) {
	  frame = 0.0;
	}
      } else {
	frame = 0;
      }
      
      dashDuration++;
      if (dashDuration > 120) {
	dashDuration = 120;
      }
      dashDistance = 0;
    } else {
      if (dir == 0) { 
	ay = -1; ax = 0;
      } else if (dir == 1) {
	ay = -1; ax = 1;
      } else if (dir == 2) {
	ay = 0; ax = 1;
      } else if (dir == 3) {
	ay = 1; ax = 1;
      } else if (dir == 4) {
	ay = 1; ax = 0;
      } else if (dir == 5) {
	ay = 1; ax = -1;
      } else if (dir == 6) {
	ay = 0; ax = -1;
      } else if (dir == 7) {
	ay = -1; ax = -1;
      }
      
      double factor = 1.0;
      if (dir % 2 != 0) {
	factor = 0.7;
      }
      
      vx = ax * 2.5 * factor;
      vy = ay * 1.25 * factor;
      
      int lastTile = map->getTile(x, y);

      x += vx;
      y += vy;

      int curTile = map->getTile(x+2*vx, y+6*vy);

      if (lastTile != curTile) {
	lastx = x;
	lasty = y;

	slipping = false;
	jumping = true;
	vz = 1.5;
	vx = ax * 1.0 * factor;
	vy = ay * 0.5 * factor;
      }
      
      dashDuration -= 2;
      if (dashDuration < 0) {
	dashDuration = 0;
      }
      dashDistance++;
    }
  } else {
    dashDistance = 0;

    lastx = x;
    lasty = y;

    x += vx;
    y += vy;

    frame = frame + 0.25;
    if (frame >= 2.0) {
      frame = 0.0;
    }
  }

  if (x < 8) {
    x = 8;
  }
  if (x > SCREEN_WIDTH - 8) {
    x = SCREEN_WIDTH - 8;
  }

  if (y < 4) {
    y = 4;
  }
  if (y > SCREEN_HEIGHT - 4) {
    y = SCREEN_HEIGHT - 4;
  }
}

void FishEater::render(int flag) {
  bool onWater = false;

  SDL_Rect src;
  src.w = 16;
  src.h = 24;

  SDL_Rect dest;
  dest.x = (short)x - 8;
  dest.y = (short)y - 18;
  dest.w = 16;
  dest.h = 24;

  if (z > 0.0) {
    src.x = 0;
    src.y = 5 * 24;
    SDL_BlitSurface(penguin, &src, screen, &dest);
  } else if (z < 0.0) {
    src.x = 6 * 16;
    src.y = 5;
    onWater = true;
  }

  if (!onWater) {
    src.x = dir * 16;
    if (slipping) {
      src.y = 4;
    } else if (jumping) {
      src.y = 4;
    } else if (walking) {
      src.y = walkingFrames[(int)frame];
    } else if (bouncing) {
      src.x = (4 + (int)frame) * 16;
      src.y = 5;  
    } else {
      src.y = 0;
    }
  }
  src.y *= 24;

  dest.x = (short)x - 8;
  dest.y = (short)y - 18 - (short)z;

  if (type == 2) {
    src.y += 144;
  }
  SDL_BlitSurface(penguin, &src, screen, &dest);

  if (playerNumber > 0) {
    src.x = playerNumber * 16;
    src.y = 5 * 24;
    dest.x = (short)x - 8;
    dest.y = (short)y - 36 - (short)z;
    SDL_BlitSurface(penguin, &src, screen, &dest);
  }

  if (dying) {
    src.x = (4 + (int)frame) * 16;
    src.y = 5 * 24;  
    src.h = 24 - 10;

    dest.x = (short)x - 8;
    if (dyingCounter > 60.0) {
      dest.y = (short)y - 20 - (short)z;
    } else {
      int sinking = (int)((1.0 - (dyingCounter / 60.0)) * 10.0);
      src.h = 24 - 10 - sinking;
      dest.y = (short)y - 20 - (short)z + sinking;
    }
    if (type == 2) {
      src.y += 144;
    }
    SDL_BlitSurface(penguin, &src, screen, &dest);
  }
}

void FishEater::addStamina(int qty) {

}

void FishEater::addScore(int qty) {

}

