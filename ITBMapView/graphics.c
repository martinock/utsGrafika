#include "grafika.h"

Point makePoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

#define SIZE 10
int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
int displayWidth, displayHeight;

/*Color struct consists of Red, Green, and Blue */
/*
Procedure untuk menggambar ke framebuffer

edge    : square size
loc_x   : x coordinate
loc_y   : y coordinate
C       : Color struct (Red, Green, Blue)
*/
void printSquare (int edge, int loc_x, int loc_y, Color C) {
    long int location;
    int i,j;
    if (((loc_x)>=0) && ((loc_x + edge)<vinfo.xres) && ((loc_y)>=0) && ((loc_y + edge)<vinfo.yres)) {
        for (i = loc_x; i < (loc_x+edge); i++) {
            for (j = loc_y; j < (loc_y+edge); j++) {
                location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;

                if (fbp + location) { //check for segmentation fault
                    if (vinfo.bits_per_pixel == 32) {
                        *(fbp + location) = C.B;            //Blue
                        *(fbp + location + 1) = C.G;        //Green
                        *(fbp + location + 2) = C.R;        //Red
                        *(fbp + location + 3) = 0;          //Transparancy
                    } else  { //assume 16bpp
                        int r = C.R;     //Red
                        int g = C.G;     //Green
                        int b = C.B;     //Blue

                        unsigned short int t = r<<11 | g << 5 | b;
                        *((unsigned short int*)(fbp + location)) = t;
                    }
                } else {
                    return;
                }
            }
        }
    }
}

void drawRect(int x, int y, int w, int h, Color c) {
  for (size_t i = 0; i < w; i++) {
    for (size_t j = 0; j < h; j++) {
      printSquare(1, x+i, y+j, c);
    }
  }
}

/*
Procedure untuk me-reset seluruh layar menjadi warna C
*/

void printBackground(Color C) {
    long int location;
    int width = displayWidth - 6;
    int height = displayHeight - 6;
    int i,j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = C.B;         //Blue
                *(fbp + location + 1) = C.G;     //Green
                *(fbp + location + 2) = C.R;     //Red
                *(fbp + location + 3) = 0;       //No transparency
            } else  { //assume 16bpp
                int r = C.R;     //Red
                int g = C.G;     //Green
                int b = C.B;     //Blue

                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
    }
}

/*
Function untuk mendapatkan warna dari suatu pixel pada posisi loc_x dan loc_y
*/
Color getColor(int loc_x, int loc_y) {
    long int location;

    Color out;
    out.R = -999; out.G = -999; out.B = -999;
    if (((loc_x)>=0) && (loc_x<vinfo.xres) && ((loc_y)>=0) && (loc_y<vinfo.yres)) {

        location = (loc_x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (loc_y+vinfo.yoffset) * finfo.line_length;

        if (fbp + location) { //check for segmentation fault
            if (vinfo.bits_per_pixel == 32) {

                out.R = (int) *(fbp + location + 2);        //Red
                out.G = (int) *(fbp + location + 1);        //Green
                out.B = (int) *(fbp + location);            //Blue
                if (out.R < 0) out.R += 256;
                if (out.G < 0) out.G += 256;
                if (out.B < 0) out.B += 256;

                *(fbp + location + 3) = 0;          //Transparancy
            } else  { //assume 16bpp
                int t = *((unsigned short int*)(fbp + location));
                out.R = (t & 63488) >> 11;     //Red
                out.G = (t & 2016) >> 5;     //Green
                out.B = t & 31;     //Blue

            }
        }
    } else {

    }
    return out;
}

/*
Function untuk mengecek apakah warna C1 == C2
Bisa diatur tingkat kesamaannya pada variable offset
*/

int colorComp(Color C1, Color C2) {
    int offset = 1;
    if ((abs(C1.R - C2.R) <= offset) && (abs(C1.G - C2.G) <= offset) && (abs(C1.B - C2.B) <= offset)) return 1;
    return 0;
}

/*
Procedure floodfill

fp_x	: fire point x
fp_y	: fire point y
C	: warna flood
fc	: warna dasar yang akan ditimpa oleh warna flood
*/

void floodFill(int fp_x, int fp_y, Color C, Color fc) {

    if (colorComp(C, fc)) {
        return;
    }

    queue pq_d;
    queue* pq = &pq_d;

    initQueue(pq);

    insertPoint(pq, makePoint(fp_x, fp_y));

    printSquare(1, fp_x, fp_y, C);

    while(!queueEmpty(pq)) {
        Point p = nextPoint(pq);
        if ((p.x>=0) && (p.x<(vinfo.xres-1)) && (p.y>=0) && (p.y<(vinfo.yres-7))) {
            if (colorComp(fc, getColor(p.x, p.y-1)) == 1) {
                printSquare(1, p.x, p.y-1, C);
                insertPoint(pq, makePoint(p.x, p.y-1));
            }

            if (colorComp(fc, getColor(p.x+1, p.y)) == 1) {
                printSquare(1, p.x+1, p.y, C);
                insertPoint(pq, makePoint(p.x+1, p.y));
            }

            if (colorComp(fc, getColor(p.x, p.y+1)) == 1) {
                printSquare(1, p.x, p.y+1, C);
                insertPoint(pq, makePoint(p.x, p.y+1));
            }

            if (colorComp(fc, getColor(p.x-1, p.y)) == 1) {
                printSquare(1, p.x-1, p.y, C);
                insertPoint(pq, makePoint(p.x-1, p.y));
            }
        }
    }
}



void initScreen() {

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    //  printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    if (vinfo.yres < 700) {
        screensize = vinfo.xres * finfo.line_length * vinfo.bits_per_pixel / 8;
    } else {
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    }



    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                fbfd, 0);
    if ((long)fbp == -1) {
    perror("Error: failed to map framebuffer device to memory");
    exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
    displayWidth = vinfo.xres;
    displayHeight = vinfo.yres;

}


Color setColor(int r, int g, int b){
    Color X;
    X.R = r;
    X.G = g;
    X.B = b;
    return X;
}

void terminate(){
    munmap(fbp, screensize);
    close(fbfd);
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