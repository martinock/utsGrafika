#include "grafika.h"

#define PI 3.14159265


Point rotatePoint(Point p ,Point pivot, float angle){
	float s = sin(angle * PI / 180);
	float c = cos(angle * PI /180);
	p.x -= pivot.x;
	p.y -= pivot.y;

	int xnew = (int) (p.x * c - p.y *s);
	int ynew = (int) (p.x * s + p.y *c);

	p.x  = xnew + pivot.x;
	p.y = ynew + pivot.y;
	return p;

}

//return rotated muliple point
Point* rotateMany(Point p, Point* p1, double angle, int length) {
  Point *temp = malloc(length);
  for (int i = 0; i < length; i++) {
    temp[i] = rotatePoint(p, p1[i], angle);
  }
  return temp;
}
