#include "base_line.h"

BaseLine::BaseLine(){
	P1 = Point();
	P2 = Point();
	tebal = 0;
}

BaseLine::BaseLine(Point _P1, Point _P2){
	P1 = _P1;
	P2 = _P2;
	tebal = 0;
}

BaseLine::BaseLine(Point _P1, Point _P2, int _tebal){
	P1 = _P1;
	P2 = _P2;
	tebal = _tebal;
}

Point BaseLine::getP1() const{
	return P1;
}
Point BaseLine::getP2() const{
	return P2;
}
int BaseLine::getTebal() const{
	return tebal;
}
void BaseLine::setP1(Point P){
	P1 = P;
}

void BaseLine::setP2(Point P){
	P2 = P;
}
void BaseLine::setTebal(int _tebal){
	tebal = _tebal;
}