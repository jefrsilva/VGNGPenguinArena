#ifndef INC_ARENA_H
#define INC_ARENA_H

#include <vector>
#include <string>
#include "SDL/SDL.h"

#include "GlobalSettings.h"

using namespace std;

const int TILE_WATER = 0;
const int TILE_ICE = 1;

const int MELT_INTERVAL = 60;
const double GRAVITY_ACCEL = 0.1;

class Position {
 public:
  int x, y;
};

class Arena {
 private:
  SDL_Surface *screen;
  SDL_Surface *tiles;

  vector<string> map;
  vector<Position> iceTiles;

  int meltCounter;

 public:
  Arena(SDL_Surface *screen);
  ~Arena();

  void update();
  void render(int i, int j);
  int getTile(double x, double y);
  Position getRandomIceTile();
};

#endif
