#include "CollisionBox.h"

int det(int x1, int y1, int x2, int y2, int x3, int y3) {
  return ((x1*y2) + (x2*y3) + (x3*y1)) -
    ((x1*y3) + (x2*y1) + (x3*y2));
}

bool lineIntersection(int x1, int y1, int x2, int y2, 
		      int x3, int y3 ,int x4, int y4) {
  return ((det(x1, y1, x2, y2, x3, y3) * det(x1, y1, x2, y2, x4, y4) < 0) && 
          (det(x3, y3, x4, y4, x1, y1) * det(x3, y3, x4, y4, x2, y2) < 0));
}

bool CollisionBox::intersects(CollisionBox other) {
  bool retValue = false;

  int ax1, ax2, ay1, ay2;
  ax1 = this->x;
  ax2 = this->x + this->w;
  ay1 = this->y;
  ay2 = this->y + this->h;

  int bx1, bx2, by1, by2;
  bx1 = other.x;
  bx2 = other.x + other.w;
  by1 = other.y;
  by2 = other.y + other.h;

  if (this->contains(bx1, by1) || this->contains(bx2, by1) ||
      this->contains(bx1, by2) || this->contains(bx2, by2)) {
    retValue = true;
  }

  if (other.contains(ax1, ay1) || other.contains(ax2, ay1) ||
      other.contains(ax1, ay2) || other.contains(ax2, ay2)) {
    retValue = true;
  }

  
  if (lineIntersection(ax1, ay1, ax2, ay1, bx1, by1, bx1, by2)) {
    retValue = true;
  }

  if (lineIntersection(ax1, ay2, ax2, ay2, bx1, by1, bx1, by2)) {
    retValue = true;
  }

  if (lineIntersection(ax1, ay1, ax2, ay1, bx2, by1, bx2, by2)) {
    retValue = true;
  }

  if (lineIntersection(ax1, ay2, ax2, ay2, bx2, by1, bx2, by2)) {
    retValue = true;
  }

  return retValue;
}

bool CollisionBox::contains(int x, int y) {
  int x1, x2, y1, y2;
  x1 = this->x;
  x2 = this->x + this->w;
  y1 = this->y;
  y2 = this->y + this->h;

  return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
