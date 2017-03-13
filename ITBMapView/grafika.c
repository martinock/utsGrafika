#include "grafika.h"
#include "framebuffer.h"

#define SIZE 10




Point makePoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}



void drawRect(int x, int y, int w, int h, Color c) {
  for (size_t i = 0; i < w; i++) {
    for (size_t j = 0; j < h; j++) {
      setXY(1, x+i, y+j, c);
    }
  }
}






/*
Procedure floodfill

fp_x	: fire point x
fp_y	: fire point y
C	: warna flood
fc	: warna dasar yang akan ditimpa oleh warna flood
*/

void floodFill(int fp_x, int fp_y, Color C, Color fc) {

    if (isColorSame(C, fc)) {
        return;
    }

    queue pq_d;
    queue* pq = &pq_d;

    initQueue(pq);

    insertPoint(pq, makePoint(fp_x, fp_y));

    setXY(1, fp_x, fp_y, C);

    while(!queueEmpty(pq)) {
        Point p = nextPoint(pq);
        if ((p.x>=0) && (p.x<(vinfo.xres-1)) && (p.y>=0) && (p.y<(vinfo.yres-7))) {
            if (isColorSame(fc, getXY(p.x, p.y-1)) == 1) {
                setXY(1, p.x, p.y-1, C);
                insertPoint(pq, makePoint(p.x, p.y-1));
            }

            if (isColorSame(fc, getXY(p.x+1, p.y)) == 1) {
                setXY(1, p.x+1, p.y, C);
                insertPoint(pq, makePoint(p.x+1, p.y));
            }

            if (isColorSame(fc, getXY(p.x, p.y+1)) == 1) {
                setXY(1, p.x, p.y+1, C);
                insertPoint(pq, makePoint(p.x, p.y+1));
            }

            if (isColorSame(fc, getXY(p.x-1, p.y)) == 1) {
                setXY(1, p.x-1, p.y, C);
                insertPoint(pq, makePoint(p.x-1, p.y));
            }
        }
    }
}









void ScaleLine(Point * p , double scalingFactorX , double scalingFactorY ){
    double xtemp = (double) p[0].x * scalingFactorX;
    double ytemp = (double) p[0].y * scalingFactorY;
    double xtemp1 = (double) p[1].x * scalingFactorX;
    double ytemp1 = (double) p[1].y * scalingFactorY;

    p[0].x = round(xtemp);
    p[0].y = round(ytemp);
    p[1].x = round(xtemp1);
    p[1].y = round(ytemp1);
}

void TranslationLine(Point *  p , int xTranslation, int yTranslation ) {
    p[0].x += xTranslation;
    p[0].y += yTranslation;
    p[1].x += xTranslation;
    p[1].y += yTranslation;
}