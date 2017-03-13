#include "grafika.h"

int cannonX;
int cannonY;
int destProjectile;

void buildCannon(int x, int y, Color c) {
    cannonX = x;
    cannonY = y;
	drawTank(makePoint(x, y));
}

void shootCannon() {
	int y = cannonY - 12;
	int x = cannonX;
	Color black;
	black.R = 0;
	black.G = 0;
	black.B = 0;

	while ((y > 80) && (destProjectile == 0)) {
		Point head[3];
	    Point body[4];

	    head[0].x = x;
	    head[1].x = x - 10;
	    head[2].x = x + 10;
	    head[0].y = y;
	    head[1].y = y + 15;
	    head[2].y = y + 15;

	    drawPolygon(3, head, black, 2);
	    floodFill(x, y+4, setColor(125, 0, 125), getColor(x, y+4));

	    body[0].x = x - 15;
	    body[1].x = x - 15;
	    body[2].x = x + 15;
	    body[3].x = x + 15;
	    body[0].y = y + 16;
	    body[1].y = y + 40;
	    body[2].y = y + 40;
	    body[3].y = y + 16;

	    drawPolygon(4, body, black, 2);
	    floodFill(x, y+18, setColor(60, 0, 60), getColor(x, y+18));

		usleep(5000);
		y -= 4;
		if ((y < 240) && (y > 120) && (x > (planeloc-115)) && (x < (planeloc + 115))) {
		    destProjectile = 1;
		    endSign = 1;
		}
	}
}
