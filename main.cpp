//main.cpp
#include <iostream>

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <thread>

#include "datastructure/point.h"
#include "datastructure/line.h"
#include "datastructure/color.h"
#include "datastructure/shape.h"
#include "datastructure/canvas.h"

using namespace std;

//framebuffer related
int fbfd = 0;
long int screensize = 0;
long int location = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
char *fbp = 0;
Point P1(200,200);
Point P2(300, 200);
int scale = 1;

Canvas *bangunan;
Canvas *clipping;
bool b, j, p;
const struct timespec* delayperframe = (const struct timespec[]){{0,2*16666667L}};

//drawer
void drawCanvas(Canvas *C){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int location = (j + vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
				(i + vinfo.yoffset) * finfo.line_length;

			if (vinfo.bits_per_pixel == 32) {
				*(fbp + location) = C->IMAGE[j][i].getB();
				*(fbp + location + 1) = C->IMAGE[j][i].getG();
				*(fbp + location + 2) = C->IMAGE[j][i].getR();
				*(fbp + location + 3) = 0;
			}
		}
	}
}

//init
void initAll(){
	//============ Init FrameBuffer
	// Open the file for reading and writing
	fbfd = open("/dev/fb0", O_RDWR);
	if (fbfd == -1) {
		perror("Error: cannot open framebuffer device");
		exit(1);
	}
	printf("The framebuffer device was opened successfully.\n");

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
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	// Map the device to memory
	fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if (*fbp == -1) {
		perror("Error: failed to map framebuffer device to memory");
		exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");
	//============ EndOF Init FrameBuffer
}

void initCaptureKeyboard(){

	// --- initialiation keystroke capture 


	// Input keyboard device file
	const char *dev = "/dev/input/event3";
	struct input_event ev;
	ssize_t n;
	int fd;

	// Open device for reference
	fd = open(dev, O_RDONLY);

	// Check if device is opened
	if (fd == -1) {
		fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
		// return EXIT_FAILURE;
	}

	// Main loop, waiting for keystroke
	while (1) {

		// get stored value on keyboard device reference file
		n = read(fd, &ev, sizeof ev);

		// check if no stored value on device file
		if (n == (ssize_t)-1) {
			if (errno == EINTR)
				continue;
			else
				break;
		} else

			// another empty
			if (n != sizeof ev) {
				errno = EIO;
				break;
			}

		// if keystroke is stored on keyboard device reference file
		if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){

			// if(ev.value == 0) // when it released

			if(ev.value == 1) // when it pressed

				switch(ev.code){
					case 12:
						// Minus triggered
						if(scale > 1) scale--;
						break;
					case 13:
						// plus triggered
						if(scale < 10) scale++;
						break;
					case 25:
						// P trigger
						p ^= 1;
						break;
					case 36:
						// J trigger
						j ^= 1;
						break;
					case 48:
						// B trigger
						b ^= 1;
						break;
					case 57:
						// Space trigger
						break;
					case 103:
						// Up arrow trigger
						P1.setY(P1.getY() - 1);
						break;
					case 105:
						// Left arrow trigger
						P1.setX(P1.getX() - 1);
						break;

					case 106:
						// Right arrow trigger
						P1.setX(P1.getX() + 1);
						break;
					case 108:
						// Down arrow trigger
						P1.setY(P1.getY() + 1);
						break;

					default:
						break;

				}

			// if(ev.value == 2) // when it repeated

			// More event code
			// https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
		}

	}
}

void garbageCaptureKeyboard(){


	// garbaging
	fflush(stdout);
	fprintf(stderr, "%s.\n", strerror(errno));

	// --------
}

void startKeystrokeThread(){
	// Constructs the new thread and runs it. Does not block execution.
	std::thread t1(initCaptureKeyboard);

	// Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
	t1.detach();
}

int main(){
	cout<<"Hello World"<<endl;


	initAll();
	bangunan = new Canvas("src/bangunanitb.txt","src/potato","src/tree.txt");
    clipping = new Canvas("src/bangunanitb.txt", "src/potato","src/tree.txt");
	
	b = true, p = true, j = true;    

	startKeystrokeThread();
	while(true){
		bangunan->setArg(p, b, j);
        
        bangunan->clear_all();
		
        bangunan->draw_all_shapes(P1, scale);
        drawCanvas(bangunan);
		nanosleep(delayperframe, NULL);
	}
	garbageCaptureKeyboard();
	return 0;
}

