#ifndef INC_TITLESTATE_H
#define INC_TITLESTATE_H

#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "GlobalSettings.h"
#include "GameState.h"

using namespace std;

class MenuOption {
 public:
  int x, y;
};

class TitleState : public GameState {
 private:
  SDL_Surface *screen;
  SDL_Surface *title;
  SDL_Surface *menu;

  Mix_Chunk *squeak;
  Mix_Chunk *scream;

  int selectedOption;
  int numPlayers;

  double vfade;
  double afade;
  double fade;
  bool fadingIn;
  bool fadingOut;

  vector<MenuOption> menuOptions;
    
 public:
  TitleState(SDL_Surface *screen);
  ~TitleState();

  void handleKeyboardEvents(SDL_Event *event);
  void update();
  void render();
};

#endif
