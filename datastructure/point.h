#ifndef POINT_H
#define POINT_H

#include "base/base_point.h"

class Point : public BasePoint{
	public:
		Point();
		Point(int,int);
		Point(const Point&);

		void translate(int, int);
		void rotate(const Point&, int);
		Point scaleUp(const Point&,double);
};

#endif
