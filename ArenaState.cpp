#include "ArenaState.h"

#include <iostream>

using namespace std;

ArenaState::ArenaState(SDL_Surface *screen, int numPlayers) {
  this->numPlayers = numPlayers;
  this->numSeals = 8;
  this->screen = screen;

  this->arena = new Arena(screen);

  this->gameover = false;
  
  SDL_Surface *tmp = SDL_LoadBMP("penguin.bmp");
  penguin = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(penguin, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(penguin->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  tmp = SDL_LoadBMP("seal.bmp");
  seal = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(seal, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(seal->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  tmp = SDL_LoadBMP("fish.bmp");
  fish = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(fish, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(fish->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  tmp = SDL_LoadBMP("interface.bmp");
  interface = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(interface, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(interface->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  tmp = SDL_LoadBMP("font.bmp");
  font = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(font, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(font->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  tmp = SDL_LoadBMP("powerups.bmp");
  powerups = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(powerups, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(powerups->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  this->squeak = Mix_LoadWAV("squeak.ogg");
  this->splash = Mix_LoadWAV("splash.ogg");
  this->scream = Mix_LoadWAV("scream.ogg");
  this->sip = Mix_LoadWAV("sip.ogg");
  this->yeah = Mix_LoadWAV("yeah.ogg");
  this->metal = Mix_LoadWAV("metal.ogg");

  this->music = Mix_LoadMUS("music.ogg");
  if (!this->music) {
    this->music = 0;
  }

  this->generator = new ChallengeGenerator(screen, font);

  this->gameover = false;
  for (int i = 0; i < numPlayers; i++) {
    players[i] = new Penguin(screen, penguin, arena, splash, scream, &effects);
    generator->registerPlayer(players[i]);
    int firstHUDx = SCREEN_WIDTH / 2;
    if (numPlayers == 1) {
      firstHUDx = (SCREEN_WIDTH / 2) - 6;
    }
    if (numPlayers == 2) {
      firstHUDx = (SCREEN_WIDTH / 2) - 66;
    }
    if (numPlayers == 3) {
      firstHUDx = (SCREEN_WIDTH / 2) - 126;    
    }
    if (numPlayers == 4) {
      firstHUDx = (SCREEN_WIDTH / 2) - 186;    
    }
    huds[i] = new PenguinHUD(screen, interface, players[i], font, firstHUDx + i * 120, 2);
    objects.push_back(players[i]);
  }

  Object *effect;
  for (int i = 0; i < numSeals; i++) {
    effect = new Seal(screen, seal, arena);
    effects.push_back(effect);
  }

  if (numPlayers >= 1) {
    players[0]->playerNumber = 1;
    players[0]->x = 168;
    players[0]->y = 126;
    players[0]->cmd_up    = SDLK_UP;
    players[0]->cmd_right = SDLK_RIGHT;
    players[0]->cmd_down  = SDLK_DOWN;
    players[0]->cmd_left  = SDLK_LEFT;
    players[0]->cmd_dash  = SDLK_RETURN;
  }

  if (numPlayers >= 2) {
    players[1]->playerNumber = 2;
    players[1]->x = 472;
    players[1]->y = 354;
    players[1]->cmd_up    = SDLK_w;
    players[1]->cmd_right = SDLK_d;
    players[1]->cmd_down  = SDLK_s;
    players[1]->cmd_left  = SDLK_a;
    players[1]->cmd_dash  = SDLK_z;
  }

  if (numPlayers >= 3) {
    players[2]->playerNumber = 3;
    players[2]->x = 168;
    players[2]->y = 354;
    players[2]->cmd_up    = SDLK_t;
    players[2]->cmd_right = SDLK_h;
    players[2]->cmd_down  = SDLK_g;
    players[2]->cmd_left  = SDLK_f;
    players[2]->cmd_dash  = SDLK_v;
  }

  if (numPlayers >= 4) {
    players[3]->playerNumber = 4;
    players[3]->x = 472;
    players[3]->y = 126;
    players[3]->cmd_up    = SDLK_i;
    players[3]->cmd_right = SDLK_l;
    players[3]->cmd_down  = SDLK_k;
    players[3]->cmd_left  = SDLK_j;
    players[3]->cmd_dash  = SDLK_m;
  }

  this->sealCounter = SEAL_INTERVAL;
  this->fishCounter = FISH_INTERVAL;
  this->eaterCounter = EATER_INTERVAL;
  this->powerupCounter = POWERUP_INTERVAL;

  highscoreState = new HighScoresState(screen, font, 190, 169);

  this->fadingIn = true;
  this->fadingOut = false;
  this->fade = 241.0;
  this->vfade = 0.0;
  this->afade = 0.5;

  if (this->music) {
    Mix_FadeInMusic(this->music, -1, 1000);
  }
}

ArenaState::~ArenaState() {
  SDL_FreeSurface(penguin);
  SDL_FreeSurface(seal);
  SDL_FreeSurface(fish);
  SDL_FreeSurface(interface);
  SDL_FreeSurface(font);
  SDL_FreeSurface(powerups);

  Mix_FreeChunk(squeak);
  Mix_FreeChunk(splash);
  Mix_FreeChunk(scream);
  Mix_FreeChunk(sip);
  Mix_FreeChunk(yeah);
  Mix_FreeChunk(metal);

  Mix_FreeMusic(music);

  list<Object *>::iterator it;

  it = objects.begin();
  while (it != objects.end()) {
    Object *obj = (*it);
    it = objects.erase(it);
    delete obj;
  }

  it = effects.begin();
  while (it != effects.end()) {
    Object *fx = (*it);
    it = effects.erase(it);
    delete fx;
  }

  delete arena;

  for (int i = 0; i < numPlayers; i++) {
    delete huds[i];
  }

  delete highscoreState;
  delete generator;
}

void ArenaState::handleKeyboardEvents(SDL_Event *event) {
  if (fadingIn || fadingOut) {
    return;
  }

  if (!gameover) {
    if (event->key.type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE) {
      if (music) {
	Mix_FadeOutMusic(1000);
      }
      fadingOut = true;
    } else {
      for (int i = 0; i < numPlayers; i++) {
	handlePenguinCommands(players[i], event);
      }
    }
  } else {
    highscoreState->handleKeyboardEvents(event);
  }
}

void ArenaState::handlePenguinCommands(Penguin *penguin, SDL_Event *event) {
  if (event->key.keysym.sym == penguin->cmd_up) {
    if (event->key.type == SDL_KEYDOWN) {
      penguin->keystate |= DIR_UP; 
    } else {
      penguin->keystate &= ~DIR_UP;
    }
  } else if (event->key.keysym.sym == penguin->cmd_right) {
    if (event->key.type == SDL_KEYDOWN) {
      penguin->keystate |= DIR_RIGHT; 
    } else {
      penguin->keystate &= ~DIR_RIGHT;
    }
  } else if (event->key.keysym.sym == penguin->cmd_down) {
    if (event->key.type == SDL_KEYDOWN) {
      penguin->keystate |= DIR_DOWN; 
    } else {
      penguin->keystate &= ~DIR_DOWN;
    }
  } else if (event->key.keysym.sym == penguin->cmd_left) {
    if (event->key.type == SDL_KEYDOWN) {
      penguin->keystate |= DIR_LEFT; 
    } else {
      penguin->keystate &= ~DIR_LEFT;
    }
  } else if (event->key.keysym.sym == penguin->cmd_dash) {
    if (event->key.type == SDL_KEYDOWN) {
      penguin->keystate |= DIR_DASH;
    } else {
      penguin->keystate &= ~DIR_DASH;
    }
  }
}

void ArenaState::update() {
  this->generator->numPlayers = numPlayers;

  if (highscoreState->fadingOut) {
    if (music) {
      Mix_FadeOutMusic(1000);
    }
    fadingOut = true;
  }

  if (fadingOut) {
    vfade += afade;
    if (vfade > 7.0) {
      vfade = 7.0;
    }
    fade += vfade;
    if (fade >= 241.0) {
      fade = 241.0;
      SDL_Event event;

      event.type = SDL_USEREVENT;
      event.user.code = EVENT_ENDSTATE;
      SDL_PushEvent(&event);
    }
  } else if (fadingIn) {
    vfade += afade;
    if (vfade > 7.0) {
      vfade = 7.0;
    }
    fade -= vfade;
    if (fade <= 0.0) {
      fade = 0;
      vfade = 0.0;
      fadingIn = false;
    }
  }

  if (!gameover) {
    int deadCount = 0;
    for (int i = 0; i < numPlayers; i++) {
      if (players[i]->isDead()) {
	deadCount++;
      }
    }
    if (deadCount == numPlayers) {
      gameover = true;
      for (int i = 0; i < numPlayers; i++) {
	highscoreState->addPlayer(i + 1, players[i]->score + players[i]->tmpScore);
      }
    }
  } else {
    highscoreState->update();
  }

  powerupCounter--;
  if (powerupCounter == 0) {
    Object *pu = new PowerUp(screen, powerups, arena);
    objects.push_back(pu);
    powerupCounter = POWERUP_INTERVAL;
  }

  eaterCounter--;
  if (eaterCounter == 0) {
    Object *p = new FishEater(screen, penguin, arena, &objects, splash, scream, &effects, generator);
    objects.push_back(p);
    eaterCounter = EATER_INTERVAL;
  }

  fishCounter--;
  if (fishCounter == 0) {
    Object *f = new Fish(screen, fish, arena);
    objects.push_back(f);
    fishCounter = FISH_INTERVAL;    
  }

  sealCounter--;
  if (sealCounter == 0) {
    Object *s = new Seal(screen, seal, arena);
    effects.push_back(s);
    sealCounter = SEAL_INTERVAL;
  }

  list<Object *>::iterator it;

  arena->update();
  
  it = objects.begin();
  while (it != objects.end()) {
    Object *obj = (*it);
    if (!obj->isDead()) {
      obj->update();
    }
    if (obj->isDead()) {
      bool destroy = true;
	
      if (obj->isPenguin()) {
	if (numPlayers == 1) {
	  if (obj == players[0]) {
	    destroy = false;
	  }
	}
	if (numPlayers == 2) {
	  if (obj == players[0] || obj == players[1]) {
	    destroy = false;
	  }
	}
	if (numPlayers == 3) {
	  if (obj == players[0] || obj == players[1] || obj == players[2]) {
	    destroy = false;
	  }
	}
	if (numPlayers == 4) {
	  if (obj == players[0] || obj == players[1] || obj == players[2] || obj == players[3]) {
	    destroy = false;
	  }
	}
      }

      if (destroy) {
	it = objects.erase(it);
	delete obj;
      } else {
	it++;
      }
    } else {
      it++;
    }
  }

  it = effects.begin();
  while (it != effects.end()) {
    Object *fx = (*it);
    fx->update();
    if (fx->isDead()) {
      it = effects.erase(it);
      delete fx;
    } else {
      it++;
    }
  }

  handleCollisions();

  generator->update();
}

void ArenaState::handleCollisions() {
  list<Object *>::iterator itA;
  list<Object *>::iterator itB;

  itA = objects.begin();
  while (itA != objects.end()) {
    Object *a = (*itA);
    if (a->isDead()) {
      itA++;
      continue;
    }
    
    itB = itA;
    itB++;
    while (itB != objects.end()) {
      Object *b = (*itB);
      if (b->isDead()) {
	itB++;
	continue;
      }
      
      if (a->collidesWith(b)) {
	if (a->isPenguin() && b->isItem()) {
	  Penguin *pa = (Penguin *)a;
	  Item *item = (Item *)b;

	  if (!item->isFish()) {
	    if (pa->playerNumber > 0) {
	      pa->stats->notify(NOTIFY_GETPOWERUP);
	      
	      Mix_PlayChannel(-1, yeah, 0); 
	      item->giveEffect(pa);
	    }
	  } else {
	    Fish *f = (Fish *)item;
	    if (f->type == 0) {
	      pa->stats->notify(NOTIFY_GETFISH);
	    } else if (f->type == 1) {
	      pa->stats->notify(NOTIFY_GETSUPERFISH);
	    } else if (f->type == 2) {
	      pa->stats->notify(NOTIFY_GETROTTENFISH);
	    }
    
	    Mix_PlayChannel(-1, sip, 0); 
	    item->giveEffect(pa);
	  }
	} else if (b->isPenguin() && a->isItem()) {
	  Penguin *pa = (Penguin *)b;
	  Item *item = (Item *)a;

	  if (!item->isFish()) {
	    if (pa->playerNumber > 0) {
	      pa->stats->notify(NOTIFY_GETPOWERUP);

	      Mix_PlayChannel(-1, yeah, 0); 
	      item->giveEffect(pa);
	    }
	  } else {
	    Fish *f = (Fish *)item;
	    if (f->type == 0) {
	      pa->stats->notify(NOTIFY_GETFISH);
	    } else if (f->type == 1) {
	      pa->stats->notify(NOTIFY_GETSUPERFISH);
	    } else if (f->type == 2) {
	      pa->stats->notify(NOTIFY_GETROTTENFISH);
	    }

	    Mix_PlayChannel(-1, sip, 0); 
	    item->giveEffect(pa);
	  }
	} else if (a->isPenguin() && b->isPenguin() && 
		   a->z > -6.0 && b->z > -6.0) {
	  if (a->vx || a->vy) {
	    a->x = a->lastx;
	    a->y = a->lasty;
	  }
	  
	  if (b->vx || b->vy) {
	    b->x = b->lastx;
	    b->y = b->lasty;
	  }

	  Penguin *pa = (Penguin *)a;
	  Penguin *pb = (Penguin *)b;

	  if (pa->slipping && !pb->slipping) {
	    if (pb->currentItem == POWERUP_STONE) {
	      Mix_PlayChannel(-1, metal, 0); 

	      pa->stats->notify(NOTIFY_GOTBOUNCED);
	      pa->bounce((pa->dir + 4) % 8, 0);
	    } else {
	      Mix_PlayChannel(-1, squeak, 0); 

	      pb->stats->notify(NOTIFY_GOTBOUNCED);
	      pb->bounce(pa->dir, pa->currentItem);

	      if (pa->currentItem != POWERUP_POWER) {
		pa->slipping = false;
		pa->dashDuration = 0;	      
	      } 
	      pa->stats->notify(NOTIFY_BOUNCED);
	      pa->addScore(SCORE_HIT);
	    }
	  }
	  if (pb->slipping && !pa->slipping) {
	    if (pa->currentItem == POWERUP_STONE) {
	      Mix_PlayChannel(-1, metal, 0); 

	      pb->stats->notify(NOTIFY_GOTBOUNCED);
	      pb->bounce((pb->dir + 4) % 8, 0);
	    } else {
	      Mix_PlayChannel(-1, squeak, 0); 

	      pa->stats->notify(NOTIFY_GOTBOUNCED);
	      pa->bounce(pb->dir, pb->currentItem);

	      if (pb->currentItem != POWERUP_POWER) {
		pb->slipping = false;
		pb->dashDuration = 0;
	      }
	      pb->stats->notify(NOTIFY_BOUNCED);
	      pb->addScore(SCORE_HIT);
	    }
	  }
	  if (pa->slipping && pb->slipping) {
	    int dashAdjustA = 0;
	    int dashAdjustB = 0;
	    if (pa->currentItem == POWERUP_STONE ||
		pa->currentItem == POWERUP_POWER) {
	      dashAdjustA += 1000;
	    }
	    if (pb->currentItem == POWERUP_STONE ||
		pb->currentItem == POWERUP_POWER) {
	      dashAdjustB += 1000;
	    }

	    if ((dashAdjustA || dashAdjustB) &&
		(pa->currentItem == POWERUP_STONE ||
		 pb->currentItem == POWERUP_STONE)) {
	      Mix_PlayChannel(-1, metal, 0); 
	    } else {
	      Mix_PlayChannel(-1, squeak, 0); 
	    }

	    if (pa->dashDistance + dashAdjustA > 
		pb->dashDistance + dashAdjustB) {
	      pb->stats->notify(NOTIFY_GOTBOUNCED);
	      pb->stats->notify(NOTIFY_LOSTSLIDE);
	      pb->bounce(pa->dir, pa->currentItem);
	      if (pa->currentItem != POWERUP_POWER) {
		pa->slipping = false;
		pa->dashDuration = 0;
	      }
	      pa->stats->notify(NOTIFY_BOUNCED);
	      pa->stats->notify(NOTIFY_WONSLIDE);
	      pa->addScore(SCORE_HIT);
	    } else if (pb->dashDistance + dashAdjustB > 
		       pa->dashDistance + dashAdjustA) {
	      pa->stats->notify(NOTIFY_GOTBOUNCED);
	      pa->stats->notify(NOTIFY_LOSTSLIDE);
	      pa->bounce(pb->dir, pb->currentItem);
	      if (pb->currentItem != POWERUP_POWER) {
		pb->slipping = false;
		pb->dashDuration = 0;
	      }
	      pb->stats->notify(NOTIFY_BOUNCED);
	      pb->stats->notify(NOTIFY_WONSLIDE);
	      pb->addScore(SCORE_HIT);
	    } else {
	      pa->stats->notify(NOTIFY_GOTBOUNCED);
	      pa->stats->notify(NOTIFY_DRAWSLIDE);
	      pb->stats->notify(NOTIFY_GOTBOUNCED);
	      pb->stats->notify(NOTIFY_DRAWSLIDE);
	      pa->bounce(pb->dir, 0);
	      pb->bounce(pa->dir, 0);
	    }
	  }
	}
      }

      itB++;
    }
    itA++;
  }

  itA = effects.begin();
  while (itA != effects.end()) {
    itB = objects.begin();
    while (itB != objects.end()) {
      Object *a = (*itA);
      Object *b = (*itB);

      if (b->isDead()) {
	itB++;
	continue;  
      }

      if (a->isSeal()) {
	if (b->isPenguin()) {
	  Seal *seal = (Seal *)(*itA);
	  Penguin *penguin = (Penguin *)(*itB);

	  if (seal->collidesWith(penguin)) {
	    penguin->die();
	  }
	}
      }
      itB++;
    }
    itA++;
  }
}

bool compObjects(const Object *a, const Object *b) {
  return a->y < b->y;
}

void ArenaState::render() {
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 64, 255));    

  list<Object *>::iterator it = objects.begin();
  it = effects.begin();
  while (it != effects.end()) {
    Object *fx = (*it);
    fx->render(1);
    it++;
  }

  objects.sort(compObjects);
  effects.sort(compObjects);

  it = objects.begin();
  while (it != objects.end()) {
    Object *obj = (*it);
    if (obj->y+3 < 0) {
      if (!obj->isDead()) {
	obj->render(0);
      }
      it++;
    } else {
      break;
    }
  }

  for (int i = 0; i < SCREEN_HEIGHT / 12; i++) {
    for (int j = 0; j < SCREEN_WIDTH / 16; j++) {
      arena->render(i, j);
    }

    while (it != objects.end()) {
      Object *obj = (*it);      

      if ((obj->y+3) >= i * 12 && (obj->y+3) < (i + 1) * 12) {
	if (!obj->isDead()) {
	  obj->render(0);
	}
	it++;
      } else {
	break;
      }
    }
  }

  while (it != objects.end()) {
    Object *obj = (*it);
    if (!obj->isDead()) {
      obj->render(0);
    }
    it++;
  }

  it = effects.begin();
  while (it != effects.end()) {
    Object *fx = (*it);
    fx->render(0);
    it++;
  }

  for (int i = 0; i < numPlayers; i++) {
    huds[i]->render();
  }

  if (gameover) {
    highscoreState->render();
  }

  generator->render();

  if (fadingIn || fadingOut) {
    SDL_Rect dest;
    dest.x = 0;
    dest.y = -1;
    dest.w = 640;
    dest.h = (int)fade;
    SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));
    
    dest.x = 0;
    dest.y = 481 - (int)fade;
    dest.w = 640;
    dest.h = (int)fade;
    SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));
  }
}

