#include "base_point.h"

BasePoint::BasePoint(){
	x = 0;
	y = 0;
}

BasePoint::BasePoint(int _x, int _y){
	x = _x, y = _y;
}

BasePoint::BasePoint(const BasePoint& BP){
	x = BP.x;
	y = BP.y;
}

int BasePoint::getX() const{
	return x;
}
int BasePoint::getY() const{
	return y;
}
void BasePoint::setX(int _x){
	x = _x;
}
void BasePoint::setY(int _y){
	y = _y;
}