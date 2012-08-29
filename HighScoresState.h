#ifndef INC_HIGHSCORESSTATE_H
#define INC_HIGHSCORESSTATE_H

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "SDL/SDL.h"

#include "GlobalSettings.h"
#include "Text.h"

using namespace std;

class PlayerInfo {
 public:
  int playerNumber;
  string name;
  int score;
};

const int MAX_SCORE_QTY = 10;

class HighScoresState {
 private:
  SDL_Surface *screen;
  SDL_Surface *font;

  int x, y;

  vector<PlayerInfo> table;
  int numPlayers;
  int curPlayer;

  Text *title;
  Text *numbers[MAX_SCORE_QTY];
  Text *names[MAX_SCORE_QTY];
  Text *scores[MAX_SCORE_QTY];
  Text *message;
  
 public:
  HighScoresState(SDL_Surface *screen, SDL_Surface *font, int x, int y);
  ~HighScoresState();

  bool fadingOut;

  void handleKeyboardEvents(SDL_Event *event);
  void update();
  void render();

  void addPlayer(int playerNumber, int score);
};

#endif
