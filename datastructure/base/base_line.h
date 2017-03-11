#ifndef BASE_LINE_H
#define BASE_LINE_H

#include "../point.h"

class BaseLine{
protected:
	Point P1, P2;
	int tebal;
public:
	BaseLine();
	BaseLine(Point, Point);
	BaseLine(Point, Point, int);
	Point getP1() const;
	Point getP2() const;
	int getTebal() const;
	
	void setP1(Point);
	void setP2(Point);
	void setTebal(int);
};

#endif