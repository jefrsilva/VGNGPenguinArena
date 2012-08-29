#ifndef INC_ITEM_H
#define INC_ITEM_H

#include "Penguin.h"

class Item : public Object {
 public:
  virtual ~Item() {};

  virtual bool isDead() = 0;
  virtual void update() = 0;
  virtual void render(int flag) = 0;

  virtual CollisionBox getCollisionBox() = 0;

  virtual void giveEffect(Penguin *penguin) = 0;

  bool isItem();
};

#endif


