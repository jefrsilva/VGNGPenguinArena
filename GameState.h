#ifndef INC_GAMESTATE_H
#define INC_GAMESTATE_H

#include "SDL/SDL.h"

class GameState {
 public:
  virtual ~GameState() {};

  virtual void handleKeyboardEvents(SDL_Event *event) = 0;
  virtual void update() = 0;
  virtual void render() = 0;
};

#endif

