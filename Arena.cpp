#include "Arena.h"

Arena::Arena(SDL_Surface *screen) {
  this->screen = screen;
  
  SDL_Surface *tmp = SDL_LoadBMP("tiles.bmp");
  tiles = SDL_DisplayFormat(tmp);
  SDL_SetColorKey(tiles, SDL_SRCCOLORKEY, 
		  SDL_MapRGB(tiles->format, 255, 0, 255));
  SDL_FreeSurface(tmp);

  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("..............############..............");
  map.push_back("...........##################...........");
  map.push_back(".........######################.........");
  map.push_back("........########################........");
  map.push_back("........########################........");
  map.push_back(".......##########################.......");
  map.push_back(".......##########################.......");
  map.push_back(".......##########################.......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back("......############################......");
  map.push_back(".......##########################.......");
  map.push_back(".......##########################.......");
  map.push_back(".......##########################.......");
  map.push_back("........########################........");
  map.push_back("........########################........");
  map.push_back(".........######################.........");
  map.push_back("...........##################...........");
  map.push_back("..............############..............");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");
  map.push_back("........................................");

  for (unsigned int i = 0; i < map.size(); i++) {
    for (unsigned int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == '#') {
	Position pos;
	pos.x = j;
	pos.y = i;

	iceTiles.push_back(pos);
      }
    }
  }

  this->meltCounter = MELT_INTERVAL;
}

Arena::~Arena() {
  SDL_FreeSurface(tiles);
}

void Arena::update() {
  meltCounter--;
  if (iceTiles.size() > 0 && meltCounter == 0) {
    int toMelt = rand() % iceTiles.size();
    Position pos = iceTiles[toMelt];
    map[pos.y][pos.x] = '.';
    iceTiles.erase(iceTiles.begin() + toMelt);
    meltCounter = MELT_INTERVAL;
  }
}

void Arena::render(int i, int j) {
  SDL_Rect src;
  src.y = 0;
  src.w = 16;
  src.h = 12;

  SDL_Rect dest;
  dest.w = 16;
  dest.h = 12;

  if (map[i][j] == '.') {
    src.x = 0;
    if (i > 0) {
      if (map[i-1][j] == '#') {
	src.x = 16;
      }
    }
  } else if (map[i][j] == '#') {
    src.x = 32;
  }
  
  dest.x = j * 16;
  dest.y = i * 12;
  SDL_BlitSurface(tiles, &src, screen, &dest);
}

int Arena::getTile(double x, double y) {
  int tile = TILE_WATER;
  int cx = (int)x / 16;
  int cy = (int)y / 12;

  if (cx >= 0 && cx < SCREEN_WIDTH / 16 && cy >=0 && cy < SCREEN_HEIGHT / 12) {
    if (map[cy][cx] == '.') {
      tile = TILE_WATER;
    } else {
      tile = TILE_ICE;
    }
  }

  return tile;
}

Position Arena::getRandomIceTile() {
  Position pos;
  if (iceTiles.size() > 0) {
    int randomIndex = rand() % iceTiles.size();
    pos = iceTiles[randomIndex];
  } else {
    pos.x = -1;
    pos.y = -1;
  }

  return pos;
}
