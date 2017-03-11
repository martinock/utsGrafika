#include "shape.h"

Shape::Shape(int _size){
	size = _size;
	P = new Point[size];
	for(int i = 0;i < size; ++i){
		P[i] = Point();
	}
}

Shape::Shape(int _size, Point* _P){
	size = _size;
	P = new Point[size];

	for(int i = 0;i < size; ++i){
		P[i] = Point(_P[i]);
	}
}

Shape::~Shape(){
	delete [] P;
}

Shape::Shape(const Shape& S){

	size = S.size;
	P = new Point[size];

	for(int i = 0;i < size; ++i){
		P[i] = Point(S.P[i]);
	}
}

Shape& Shape::operator=(const Shape& S){

	delete [] P;
	size = S.size;
	P = new Point[size];

	for(int i = 0;i < size; ++i){
		P[i] = Point(S.P[i]);
	}

	return *this;
}

Point* Shape::getAllPoint() const{
	return P;
}
Point Shape::getPoint(int idx) const{
	return P[idx];
}
int Shape::getSize() const{
	return size;
}

void Shape::setAllPoint(Point* _P){
	delete [] P;
	P = new Point[size];
	for(int i = 0;i < size; ++i){
		P[i] = Point(_P[i]);
	}
}
void Shape::setPoint(int idx, Point _P){
	P[idx] = _P;
}