#include "Penguin.h"

Penguin::Penguin() {

}

Penguin::Penguin(SDL_Surface *screen, SDL_Surface *image, Arena *map, Mix_Chunk *splash, Mix_Chunk *scream, list<Object *> *effects) {
  this->screen = screen;
  this->penguin = image;
  this->map = map;
  this->splash = splash;
  this->scream = scream;

  this->dead = false;
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
  this->bouncing = false;
  this->jumping = false;
  
  this->dashDuration = 120;
  this->dashDistance = 0;
  this->passable = false;
  this->stamina = 100;

  this->score = 0;
  this->tmpScore = 0;
  this->scoreCounter = 0;

  this->effects = effects;

  this->currentItem = 0;
  this->powerupDuration = 0;

  this->wonChallengeCounter = 0;

  this->stats = new ChallengeStats(false);
}

Penguin::~Penguin() {
  delete stats;
}

bool Penguin::isDead() {
  return dead;
}

void Penguin::update() {
  wonChallengeCounter--;
  if (wonChallengeCounter < 0) {
    wonChallengeCounter = 0;
  }
  
  double speedFactor = 1.0;
  if (currentItem == POWERUP_SPEED) {
    speedFactor = 2.0;
  }

  if (currentItem > 0) {
    powerupDuration--;
    if (powerupDuration <= 0) {
      currentItem = 0;
      powerupDuration = 0;
    }
  }

  scoreCounter++;
  if (scoreCounter > 1 && tmpScore > 0) {
    tmpScore--;
    score++;
    scoreCounter = 0;
  }

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
      if (currentItem == POWERUP_CONFUSION) {
	dir = (dir + 4) % 8;
      }
      
      double waterSlow = 1.0;
      if (z == zlimit && z < 0.0) {
	stats->notify(NOTIFY_ONWATER);
	if (keystate == 0) {
	  stats->notify(NOTIFY_NOTMOVINGWATER);
	} else {
	  stats->notify(NOTIFY_MOVEDONWATER);
	}
	waterSlow = (((double)stamina / 120.0) * 0.8) + 0.2;
      }

      if (z == zlimit && z == 0.0) {
	stats->notify(NOTIFY_ONICE);
	if (keystate == 0) {
	  stats->notify(NOTIFY_NOTMOVINGICE);
	} else {
	  stats->notify(NOTIFY_MOVEDONICE);
	}	
      }

      double factor = 1.0;
      if (dir % 2 != 0) {
	factor = 0.7;
      }
      
      vx = ax * 1.0 * factor * speedFactor;
      vy = ay * 0.5 * factor * speedFactor;

      if (currentItem == POWERUP_CONFUSION) {
	vx *= -1;
	vy *= -1;
      }
      
      int lastTile = map->getTile(x, y);

      x += (vx * waterSlow);
      y += (vy * waterSlow);

      int curTile = map->getTile(x+4*vx, y+12*vy);

      if (lastTile != curTile) {
	if (lastTile == TILE_WATER) {
	  stats->notify(NOTIFY_LEFTWATER);
	} else {
	  stats->notify(NOTIFY_ENTEREDWATER);
	}

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
      
      if (currentItem == POWERUP_DASH) {
	dashDuration+=2;
      } else {
	dashDuration++;
      }
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

      stats->notify(NOTIFY_ONICE);
      
      double factor = 1.0;
      if (dir % 2 != 0) {
	factor = 0.7;
      }
      
      vx = ax * 2.5 * factor * speedFactor;
      vy = ay * 1.25 * factor * speedFactor;
      
      int lastTile = map->getTile(x, y);

      x += vx;
      y += vy;

      int curTile = map->getTile(x+2*vx, y+6*vy);

      if (lastTile != curTile) {
	if (lastTile == TILE_WATER) {
	  stats->notify(NOTIFY_LEFTWATER);
	} else {
	  stats->notify(NOTIFY_ENTEREDWATER);
	}

	lastx = x;
	lasty = y;

	slipping = false;
	jumping = true;
	vz = 1.5;
	vx = ax * 1.0 * factor;
	vy = ay * 0.5 * factor;
      }
      
      dashDistance++;
      dashDuration -= 2;
      if (dashDuration <= 0) {
	dashDuration = 0;
	if (dashDistance == 60) {
	  stats->notify(NOTIFY_FULLSLIDE);
	}
      }
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

void Penguin::render(int flag) {
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

  if (currentItem > 0) { 
    src.x = (currentItem - 1) * 16;
    src.y = 12 * 24;
    SDL_BlitSurface(penguin, &src, screen, &dest);
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

  SDL_BlitSurface(penguin, &src, screen, &dest);

  if (playerNumber > 0) {
    if (wonChallengeCounter > 0) {
      src.x = (playerNumber - 1) * 16;
      if (wonChallengeCounter % 8 > 3) {
	src.y = 13 * 24;
	dest.x = (short)x - 8;
	dest.y = (short)y - 36 - (short)z;
	SDL_BlitSurface(penguin, &src, screen, &dest);      
      }
    } else {
      src.x = (playerNumber - 1) * 16;
      src.y = 11 * 24;
      dest.x = (short)x - 8;
      dest.y = (short)y - 36 - (short)z;
      SDL_BlitSurface(penguin, &src, screen, &dest);
    }
  }

  if (dying) {
    if ((int)frame) {
      Object *fx = new WaterFX(screen, x, y);
      effects->push_back(fx);
    }

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
    SDL_BlitSurface(penguin, &src, screen, &dest);
  }
}

CollisionBox Penguin::getCollisionBox() {
  CollisionBox box;

  box.x = (int)this->x - 8 + 4;
  box.y = (int)this->y - 18 + 15;
  box.w = 9;
  box.h = 7;
  box.z = (int)z;
  box.zh = 12;
  if (dying) {
    box.w = -1;
    box.h = -1;
  }

  return box;
}

bool Penguin::isPenguin() {
  return true;
}

void Penguin::bounce(int dir, int type) {
  stats->notify(NOTIFY_MOVEDONICE);

  vz = 2.0 + (1.0 - ((double)stamina / 100.0)) * 3.0;
  if (type == POWERUP_POWER) {
    vz = 7.0;
  }

  jumping = false;
  walking = false;
  slipping = false;
  bouncing = true;

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

  double factor = 1.0 + (1.0 - ((double)stamina / 100.0)) * 2.0;
  if (dir % 2 != 0) {
    factor = 0.7 * factor;
  }
  
  vx = ax * factor;
  vy = ay * 0.5 * factor;

  stamina -= BOUNCE_STAMINA_REDUCTION;
  if (stamina < 0) {
    stamina = 0;
  }
}

void Penguin::die() {
  stats->notify(NOTIFY_MOVEDONWATER);

  Mix_PlayChannel(-1, scream, 0); 
  currentItem = 0;
  powerupDuration = 0;
  dying = true;
  dyingCounter = 90.0;
  walking = false;
  bouncing = false;
  slipping = false;
  jumping = false;
  vx = 0;
  vy = 0;
  ax = 0;
  ay = 0;
}

void Penguin::addStamina(int qty) {
  this->stamina += qty;
  if (this->stamina < 0) {
    this->stamina = 0;
  }
  if (this->stamina > 100) {
    this->stamina = 100;
  }
}

void Penguin::addScore(int qty) {
  stats->notifyScore(qty);
  this->tmpScore += qty;
}

void Penguin::wonChallenge() {
  wonChallengeCounter = 120;
}
