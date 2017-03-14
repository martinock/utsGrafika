#include "filling.h"



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

void raster_fill(int y_min, int y_max, int x_min, int x_max) {


    for (int i = y_min; i < y_max; ++i) {
        for (int j = x_min; j < x_max; ++j) {
            if (isColorSame(getXY(j, i), setColor(255,255,255))) { // iteration one line in minimapand view
                while (!isColorSame(getXY(j+1, i), setColor(255,255,255))) {
                    // coloring 
                    setXY(1, j+1, i, setColor(255,255,255));
                } // finish iteration one part of the line
                continue;
            } else if (isColorSame(getXY(j, i), setColor(255,0,0))) { // iteration one line in clipping window
                while (isColorSame(getXY(j+1, i), setColor(0,0,0))) {
                    setXY(1, j+1, i, setColor(255,0,0));
                }
                continue;
            } else {
                // nothing
            }
        }
    }
}