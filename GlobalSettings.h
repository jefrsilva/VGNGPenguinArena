#ifndef INC_GLOBALSETTINGS_H
#define INC_GLOBALSETTINGS_H

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

const int EVENT_NEWGAME = 1;
const int EVENT_ENDSTATE = 2;

const int POWERUP_POWER = 1;
const int POWERUP_STONE = 2;
const int POWERUP_DASH  = 3;
const int POWERUP_SPEED = 4;
const int POWERUP_CONFUSION = 5;

const int CHALLENGE_NEXT_INTERVAL = 600;

const int NOTIFY_GETPOWERUP     = 1;
const int NOTIFY_GETFISH        = 2;
const int NOTIFY_GETSUPERFISH   = 3;
const int NOTIFY_GETROTTENFISH  = 4;
const int NOTIFY_GOTBOUNCED     = 5;
const int NOTIFY_BOUNCED        = 6;
const int NOTIFY_WONSLIDE       = 7;
const int NOTIFY_DRAWSLIDE      = 8;
const int NOTIFY_LOSTSLIDE      = 9;
const int NOTIFY_NOTMOVINGWATER = 10;
const int NOTIFY_MOVEDONWATER   = 11;
const int NOTIFY_NOTMOVINGICE   = 12;
const int NOTIFY_MOVEDONICE     = 13;
const int NOTIFY_ENTEREDWATER   = 14;
const int NOTIFY_LEFTWATER      = 15;
const int NOTIFY_ONWATER        = 16;
const int NOTIFY_ONICE          = 17;
const int NOTIFY_FULLSLIDE      = 18;

#endif
