#include "Object.h"

bool Object::collidesWith(Object *other) {
  bool collides = false;

  CollisionBox a = this->getCollisionBox();
  CollisionBox b = other->getCollisionBox();

  if (a.w < 0 || b.w < 0) {
    return false;
  }
  
  if (this->z == other->z) {
    collides = a.intersects(b);
  } else if (this->z >= 0.0 && other->z >= 0.0) {
    CollisionBox ba = this->getCollisionBox();
    CollisionBox bb = other->getCollisionBox();
    
    collides = a.intersects(b);
    if (collides && 
	((bb.z <= ba.z && ba.z <= bb.z + bb.zh) ||
	 (bb.z <= ba.z + ba.zh && ba.z + ba.zh <= bb.z + bb.zh) ||
	 (ba.z <= bb.z && bb.z <= ba.z + ba.zh) ||
	 (ba.z + ba.zh <= bb.z + bb.zh && bb.z + bb.zh <= ba.z + ba.zh))) {
      collides = true;
    } else {
      collides = false;
    }
  }
  
  return collides;
}

bool Object::isPenguin() {
  return false;
}

bool Object::isSeal() {
  return false;
}

bool Object::isFish() {
  return false;
}

bool Object::isItem() {
  return false;
}

double Object::distanceTo(Object *object) {
  double deltax = this->x - object->x;
  double deltay = this->y - object->y;
  double distance = (deltax * deltax) + (deltay * deltay);

  return distance;
}
