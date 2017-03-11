#include "base_color.h"

BaseColor::BaseColor(){
	R = 0;
	G = 0;
	B = 0;
}

BaseColor::BaseColor(int _R, int _G, int _B){
	R = _R;
	G = _G;
	B = _B;
}

int BaseColor::getR() const{
	return R;
}

int BaseColor::getG() const{
	return G;
}

int BaseColor::getB() const{
	return B;
}

void BaseColor::setR(int _R){
	R = _R;
}
void BaseColor::setG(int _G){
	G = _G;
}
void BaseColor::setB(int _B){
	B = _B;
	
}
