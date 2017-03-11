#ifndef LINE_H
#define LINE_H

#include "base/base_line.h"
 
class Line : BaseLine{
public:
	Line();
	Line(Point, Point);
	Line(Point, Point, int);

	void translate(int, int);
	void rotate(const Point&, int);
	Line scaleUp(const Point&, double);
};

#endif
