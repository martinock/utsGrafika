#include "line.h"

Line::Line() : BaseLine(){
	//do nothing
}

Line::Line(Point _P1, Point _P2) : BaseLine(_P1, _P2){
	//do nothing
}

Line::Line(Point _P1, Point _P2, int _tebal) : BaseLine(_P1, _P2, _tebal){
	//do nothing
}

//helper function
void Line::translate(int deltaX, int deltaY){
	P1.translate(deltaX, deltaY);
	P2.translate(deltaX, deltaY);
}

void Line::rotate(const Point& center, int degree){
	P1.rotate(center, degree);
	P2.rotate(center, degree);
}
Line Line::scaleUp(const Point& center, double scale){
	Line L;
	L.setP1(P1.scaleUp(center, scale));
	L.setP2(P2.scaleUp(center, scale));
}
