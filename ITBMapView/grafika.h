#ifndef GRAFIKA_H
#define GRAFIKA_H

#include <fcntl.h>
#include <linux/fb.h>
#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

#define ENTER_KEYPRESS 10
#define LEFT_KEYPRESS 68
#define RIGHT_KEYPRESS 67
#define UP_KEYPRESS 66
#define DOWN_KEYPRESS 65
#define ZOOMIN_KEYPRESS 61
#define ZOOMOUT_KEYPRESS 45
#define TOGGLE_BUILDING_KEYPRESS 122
#define TOGGLE_ROADS_KEYPRESS 120
#define TOGGLE_TREES_KEYPRESS 99


typedef struct {
    int x;
    int y;
} Point;

typedef struct {
  Point pos;
  Point vel;
} PhysicsPoint;

typedef struct {
    int R;
    int G;
    int B;
} Color;

typedef struct qi_t* qi_p;

typedef struct qi_t {
    qi_p next;
    Point data;
} queueItem;

typedef struct {
    queueItem* first;
    queueItem* last;
} queue;

int fbfd;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize;
char *fbp;
int displayWidth, displayHeight;

Point explosionPoint[11];
int planeloc;
int endSign;


//point
Point makePoint(int x, int y);


//basic framebuffer primitive
void initScreen();
Color setColor(int r, int g, int b);
Color getColorRGB(int r, int g, int b);
Color getColor(int loc_x, int loc_y);
void printBackground(Color C);
void terminate();


//basic geometry
void drawBresenhamLine (Point P1, Point P2, Color C, int W);
void drawPolyline (int n, Point *P, Color C, int W);
void drawPolygon (int n, Point *P, Color C, int W);
void drawExplosion (Point initialPoint, int n, Point *P, int scaleFactor);
void drawCircle (int radius, Point P, int W, Color C);
void drawCircleHalf (int radius, Point P, int W, Color C);


//transition
Point rotatePoint(Point p ,Point pivot, float angle);
Point* rotateMany(Point p, Point* p1, double angle, int length);
void ScaleLine(Point * p , double scalingFactorX , double scalingFactorY );
void TranslationLine(Point *  p , int xTranslation, int yTranslation);


//complex drawings
void buildCannon(int x, int y, Color c);
void shootCannon();
void drawBaling(int x, int y, int rotation);
void drawTire(Point P, int rot);
void drawPlane(Point p, int direction, Color planeColor);
void drawBrokenPlaneCockpit(Point lastPoint);
void drawBrokenPlaneBody(Point lastPoint);
void drawBrokenPlaneWings(Point lastPoint);
void drawParachute(Point anc);
void drawTank(Point anc);




void drawRect(int x, int y, int w, int h, Color c);
int colorComp(Color C1, Color C2);
void floodFill(int fp_x, int fp_y, Color C, Color fc);


int getch(void);



//queue
void initQueue(queue* q);
char queueEmpty(queue* q);
void insertPoint(queue* q, Point d);
Point nextPoint(queue* q);

PhysicsPoint makePhysicsPoint(int x, int y, int xvel, int yvel);
void updatePhysicsPoint(PhysicsPoint* pp);



#endif
