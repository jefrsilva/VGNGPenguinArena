#include "HighScoresState.h"

bool cmpPlayerInfo(const PlayerInfo &a, const PlayerInfo &b) {
  return (a.score >= b.score);
}

HighScoresState::HighScoresState(SDL_Surface *screen, SDL_Surface *font, int x, int y) {
  this->screen = screen;
  this->font = font;

  this->x = x;
  this->y = y;


  ifstream highscoreFile;
  highscoreFile.open("./scoretable");
  
  PlayerInfo player;
  while (highscoreFile >> player.name >> player.score) {
    player.playerNumber = 0;
    table.push_back(player);
  }
  
  title = new Text(screen, font, 320, y, ALIGN_CENTER);
  title->text = "HIGH SCORES";

  message = new Text(screen, font, 320, y - 12 + 164, ALIGN_CENTER);
  message->text = "PRESS ANY KEY TO CONTINUE";

  for (int i = 0; i < MAX_SCORE_QTY; i++) {
    numbers[i] = new Text(screen, font, x + 14, y + 24 + i * 12, ALIGN_RIGHT);
    names[i] = new Text(screen, font, x + 33, y + 24 + i * 12, ALIGN_LEFT);
    scores[i] = new Text(screen, font, x + 240, y + 24 + i * 12, ALIGN_LEFT);
    
    stringstream out;
    out << i + 1 << ".";
    numbers[i]->text = out.str();

    out.str("");
    out << table[i].score;
    scores[i]->text = out.str();
  }

  highscoreFile.close();

  this->numPlayers = 0;
  this->curPlayer = 1;

  this->fadingOut = false;
}

HighScoresState::~HighScoresState() {
  delete title;
  for (int i = 0; i < MAX_SCORE_QTY; i++) {
    delete numbers[i];
    delete names[i];
    delete scores[i];
  }
  delete message;
}

void HighScoresState::handleKeyboardEvents(SDL_Event *event) {
  if (event->key.type == SDL_KEYDOWN) {
    if (curPlayer > numPlayers) {
      fadingOut = true;
    } else {
      string c = string(SDL_GetKeyName(event->key.keysym.sym));
      bool allowEnd = true;
      for (int i = 0; i < MAX_SCORE_QTY; i++) {
	if (table[i].playerNumber == curPlayer) {
	  if (table[i].name.length() == 0) {
	    allowEnd = false;
	  }
	}
      }
      if (c == "return") {
	if (allowEnd) {
	  bool found = false;
	  while (!found && curPlayer <= numPlayers) {
	    curPlayer++;
	    for (int i = 0; i < MAX_SCORE_QTY; i++) {
	      if (table[i].playerNumber == curPlayer) {
		found = true;
	      }
	    }
	  }
	  if (curPlayer > numPlayers) {
		ofstream highscoreFile;  
	    highscoreFile.open("./scoretable", fstream::trunc);
	    for (int i = 0; i < MAX_SCORE_QTY; i++) {
	      highscoreFile << table[i].name << " " << table[i].score << endl;
	    }
	    highscoreFile.close();
	  }
	}
      } else if ((c[0] >= 'a' && c[0] <= 'z') || 
		 (c[0] >= '0' && c[0] <= '9') || c == "backspace") {
	for (int i = 0; i < MAX_SCORE_QTY; i++) {
	  if (table[i].playerNumber == curPlayer) {
	    if (c == "backspace") {
	      if (table[i].name.length() > 0) {
		table[i].name = table[i].name.substr(0, table[i].name.length() - 1);
	      }
	    } else if (c[0] >= 'a' && c[0] <= 'z' && c.length() == 1) {
	      if (table[i].name.length() < 30) {
		c[0] += ('A' - 'a');
		table[i].name += c[0];
	      }
	    } else if (c[0] >= '0' && c[0] <= '9' && c.length() == 1) {
	      if (table[i].name.length() < 30) {
		table[i].name += c[0];
	      }
	    }
	  }
	}
      }
    }
  }
}

void HighScoresState::update() {

}

void HighScoresState::render() {
  SDL_Rect dest;
  dest.x = x - 32;
  dest.w = 324;
  dest.y = y - 12;
  dest.h = 188;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 128, 128, 128));

  dest.x = x - 30;
  dest.w = 322;
  dest.y = y - 10;
  dest.h = 186;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));

  dest.x = x - 30;
  dest.w = 320;
  dest.y = y - 10;
  dest.h = 184;
  SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 64, 64, 64));

  for (int i = 0; i < MAX_SCORE_QTY; i++) {
    dest.x = x - 30;
    dest.w = 320;
    dest.y = y + 23 + i * 12;
    dest.h = 11;
    if (table[i].playerNumber == 1) {
      SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 255, 0, 0));
    } else if (table[i].playerNumber == 2) {
      SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 255, 255, 0));
    } else if (table[i].playerNumber == 3) {
      SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 255, 0));
    } else if (table[i].playerNumber == 4) {
      SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 96, 255));
    }    
  }

  title->render();
  for (int i = 0; i < MAX_SCORE_QTY; i++) {
    numbers[i]->render();

    if (table[i].playerNumber == curPlayer) {
      if (table[i].name.length() == 30) {
	names[i]->text = table[i].name + '[';
      } else {
	names[i]->text = table[i].name + '_';
      }
    } else {
      names[i]->text = table[i].name;
    }
    names[i]->render();

    stringstream out;
    out << table[i].score;
    scores[i]->text = out.str();
    scores[i]->render();
  }
  if (curPlayer > numPlayers) {
    message->render();
  }
}

void HighScoresState::addPlayer(int playerNumber, int score) {
  PlayerInfo player;
  player.name = "";
  player.playerNumber = playerNumber;
  player.score = score;

  table.push_back(player);

  sort(table.begin(), table.end(), cmpPlayerInfo);
  numPlayers++;

  curPlayer = numPlayers + 1;
  for (int i = 0; i < MAX_SCORE_QTY; i++) {
    if (table[i].playerNumber > 0) {
      if (table[i].playerNumber < curPlayer) {
	curPlayer = table[i].playerNumber;
      }
    }
  }
}

