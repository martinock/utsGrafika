#ifndef BASE_POINT_H
#define BASE_POINT_H

class BasePoint{
	private:
		int x, y;
	public:
		BasePoint();
		BasePoint(int, int);
		BasePoint(const BasePoint&);

		int getX() const;
		int getY() const;
		void setX(int);
		void setY(int);
};

#endif