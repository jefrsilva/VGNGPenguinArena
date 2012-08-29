#ifndef INC_COLLISIONBOX_H
#define INC_COLLISIONBOX_H

class CollisionBox {
 public:
  int x, y, z, w, h, zh;

  bool intersects(CollisionBox other);
  bool contains(int x, int y);
};

#endif

