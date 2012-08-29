#include "TitleState.h"

TitleState::TitleState(SDL_Surface *screen) {
  this->screen = screen;

  SDL_Surface *tmp = SDL_LoadBMP("title.bmp");
  title = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);

  tmp = SDL_LoadBMP("menu.bmp");
  menu = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(menu, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(menu->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  this->squeak = Mix_LoadWAV("squeak.ogg");
  this->scream = Mix_LoadWAV("scream.ogg");

  MenuOption option;
  option.x = 10;
  option.y = 240;
  menuOptions.push_back(option);
  option.x = 150;
  option.y = 210;
  menuOptions.push_back(option);
  option.x = 290;
  option.y = 180;
  menuOptions.push_back(option);
  option.x = 430;
  option.y = 150;
  menuOptions.push_back(option);
  option.x = 460;
  option.y = 340;
  menuOptions.push_back(option);

  this->selectedOption = 0;

  this->fadingIn = false;
  this->fadingOut = false;
  this->fade = 0.0;
  this->vfade = 0.0;
  this->afade = 0.5;
}

TitleState::~TitleState() {
  SDL_FreeSurface(title);
  SDL_FreeSurface(menu);

  Mix_FreeChunk(squeak);
  Mix_FreeChunk(scream);
}

void TitleState::handleKeyboardEvents(SDL_Event *event) {
  if (fadingIn || fadingOut) {
    return;
  }

  if (event->key.type == SDL_KEYDOWN) {
    if (event->key.keysym.sym == SDLK_UP ||
	event->key.keysym.sym == SDLK_RIGHT) {
      selectedOption = (selectedOption + 1) % menuOptions.size();
      Mix_PlayChannel(-1, squeak, 0); 
    } else if (event->key.keysym.sym == SDLK_DOWN ||
	       event->key.keysym.sym == SDLK_LEFT) {
      selectedOption = (selectedOption - 1 + menuOptions.size()) % 
	menuOptions.size();
      Mix_PlayChannel(-1, squeak, 0); 
    } else if (event->key.keysym.sym == SDLK_SPACE ||
	       event->key.keysym.sym == SDLK_RETURN) {
      fadingOut = true;
      Mix_PlayChannel(-1, scream, 0);       
    }
  }
}

void TitleState::update() {
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
      if (selectedOption >= 0 && selectedOption <= 3) {
	numPlayers = selectedOption + 1;
	event.user.code = EVENT_NEWGAME;
	event.user.data1 = &numPlayers;
	SDL_PushEvent(&event);	
	fadingOut = false;
	fadingIn = true;
	vfade = 0.0;
      } else if (selectedOption == 4) {
	event.user.code = EVENT_ENDSTATE;
	SDL_PushEvent(&event);
	fadingOut = false;
	fadingIn = true;
	vfade = 0.0;
      }
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
}

void TitleState::render() {
  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = 640;
  src.h = 480;

  SDL_Rect dest;
  dest.x = 0;
  dest.y = 0;
  dest.w = 640;
  dest.h = 480;
  SDL_BlitSurface(title, &src, screen, &dest);

  for (unsigned int i = 0; i < menuOptions.size(); i++) {
    if ((unsigned int)selectedOption == i) {
      src.x = 0;
    } else {
      src.x = 180;
    }
    src.y = i * 100;
    src.w = 180;
    src.h = 100;
    
    dest.x = menuOptions[i].x;
    dest.y = menuOptions[i].y;
    dest.w = 180;
    dest.h = 100;
    SDL_BlitSurface(menu, &src, screen, &dest);
  }

  if (fadingIn || fadingOut) {
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
