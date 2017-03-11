#ifndef BASE_COLOR_H
#define BASE_COLOR_H

class BaseColor{
private:
	int R, G, B;
public:
	BaseColor();
	BaseColor(int,int,int);
	
	int getR() const;
	int getG() const;
	int getB() const;

	void setR(int);
	void setG(int);
	void setB(int);
};

#endif
