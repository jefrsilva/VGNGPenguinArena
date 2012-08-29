#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_getenv.h"

#include "GlobalSettings.h"
#include "GameState.h"
#include "TitleState.h"
#include "ArenaState.h"
#include "Text.h"

using namespace std;

int main(int argc, char *argv[]) {
  bool windowed = false;
  if (argc >= 2) {
    string option;
    option = string(argv[1]);
    if (option[0] == '-' && option[1] == 'w') {
      windowed = true;
    }
  }

  srand((unsigned)time(0));
	
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
    cerr << "Unable to init SDL: " << SDL_GetError() << endl;
    exit(1);
  }

//   putenv("SDL_VIDEODRIVER=directx");

  SDL_Surface *screen;
  if (!windowed) {
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_DOUBLEBUF | SDL_FULLSCREEN);
  } else {
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_DOUBLEBUF);
  }

  if (!screen) {
    cout << "Unable to set video mode: " << SDL_GetError() << endl;
    exit(1);
  }

  SDL_WM_SetCaption	("Incomprehensible Penguin Arena", 0);
  SDL_ShowCursor(SDL_DISABLE);

  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0) {
    cout << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
    exit(1);
  }

  Mix_Volume(-1, 128);

  SDL_Surface *tmp = SDL_LoadBMP("font.bmp");
  SDL_Surface *font = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(font, SDL_SRCCOLORKEY, 
  SDL_MapRGB(font->format, 255, 0, 255));

  SDL_FreeSurface(tmp);

  stack<GameState *> states;
  states.push(new TitleState(screen));

  GameState *currentState;

  unsigned int lastTime = 0;
  unsigned int currentTime = 0;
  unsigned int elapsedTime = 0;
  unsigned int fpsTime = 0;
  unsigned int frameCounter = 0;
  unsigned int fps = 0;

  Text *text = new Text(screen, font, 2, 2, ALIGN_LEFT);

  bool takeScreenshot = false;
  bool finished = false;
  while (!finished) {
    if (!states.empty()) {
      currentState = states.top();
    } else {
      finished = true;
      continue;
    }
    
    bool nextState = false;
    SDL_Event event;
    while (SDL_PollEvent(&event) && !nextState) {
      switch (event.type) {

      case SDL_USEREVENT:
	if (event.user.code == EVENT_NEWGAME) {
	  GameState *newState = new ArenaState(screen, *(int *)event.user.data1);
	  states.push(newState);
	} else if (event.user.code == EVENT_ENDSTATE) {
	  delete currentState;
	  states.pop();
	  nextState = true;
	}
	break;

      case SDL_KEYUP:
      case SDL_KEYDOWN:
	if (event.key.keysym.sym == SDLK_PRINT) {
	  takeScreenshot = true;
	}

	currentState->handleKeyboardEvents(&event);
	break;
	
      case SDL_QUIT:
	finished = true;
	continue;
      }
    }

    if (nextState) {
      continue;
    }

    currentTime = SDL_GetTicks();
    fpsTime += currentTime - lastTime;
    elapsedTime += currentTime - lastTime;
    lastTime = currentTime;

    if (fpsTime >= 960) {
      fps = frameCounter;
      frameCounter = 0;
      fpsTime -= 960;
    }

    bool updated = false;
    while (elapsedTime >= 16) {
      currentState->update();
      elapsedTime -= 16;
      updated = true;
    }
    
    if (updated) {
      frameCounter++;
      currentState->render();
      stringstream out;
      out << fps << " FPS";
      text->text = out.str();
      text->render();
      if (takeScreenshot) {
	SDL_SaveBMP(screen, "sshot.bmp");
	takeScreenshot = false;
      }
      SDL_Flip(screen);
    }
  }

  while (!states.empty()) {
    currentState = states.top();
    states.pop();
    delete currentState;
  }

  Mix_CloseAudio();

  SDL_FreeSurface(font);
  SDL_FreeSurface(screen);

  SDL_Quit();

  return 0;
}
