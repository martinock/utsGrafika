#include "point.h"
#include <cmath>

Point::Point() : BasePoint(){
	//do nothing
}

Point::Point(int _x, int _y) : BasePoint(_x, _y){
	//do nothing
}

Point::Point(const Point& P) : BasePoint(P){
	//do nothing
}

void Point::translate(int deltaX, int deltaY){
	setX(getX() + deltaX);
	setY(getY() + deltaY);
}

void Point::rotate(const Point& P, int degree){

	double deg_in_pi = std::acos(-1) * degree / 180.0;
	double cosinus = std::cos(deg_in_pi);
	double sinus = std::sin(deg_in_pi);

	Point temp;
	temp.setX((int) (cosinus * (getX() - P.getX()) - sinus * (getY() - P.getY())) + P.getX());
	temp.setY((int) (sinus * (getX() - P.getX()) + cosinus * (getY() - P.getY())) + P.getY());

	setX(temp.getX());
	setY(temp.getY());

}

Point Point::scaleUp(const Point& center, double scale){
	Point P_new;
	P_new.setX((int)((getX() - center.getX()) * scale) + center.getX());
	P_new.setY((int)((getY() - center.getY()) * scale) + center.getY());
	return P_new;
}
