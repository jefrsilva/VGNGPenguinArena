#ifndef INC_OBJECT_H
#define INC_OBJECT_H

#include "CollisionBox.h"
#include "GlobalSettings.h"

const double MAX_DISTANCE = 
  (SCREEN_WIDTH * SCREEN_WIDTH) + (SCREEN_WIDTH * SCREEN_WIDTH);

class Object {
 public:
  double x, y, z;
  double vx, vy, vz;
  double lastx, lasty;
  bool passable;

  virtual ~Object() {};

  virtual bool isDead() = 0;
  virtual void update() = 0;
  virtual void render(int flag) = 0;

  virtual bool collidesWith(Object *object);
  virtual CollisionBox getCollisionBox() = 0;

  virtual bool isPenguin();
  virtual bool isSeal();
  virtual bool isFish();
  virtual bool isItem();

  virtual double distanceTo(Object *object);
};

#endif

