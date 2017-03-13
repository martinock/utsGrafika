#include "color.h"
#include "framebuffer.h"
#include "grafika.h"
#include "clipping.h"



double left = 0;
double up = 0;
double scaleFactor = 1;
unsigned char drawBuildings = 1;
unsigned char drawRoads = 1;
unsigned char drawTrees = 1;
pthread_t keypressListener;

unsigned char between(int a, int b, int x) {
	return x > a && x < b;
}

unsigned char isLineSane(int n, Point* line) {
	for (size_t i = 0; i < n; i++) {
		// Should be fine for a few years
		if (!between(-50000, 100000, line[i].x) || !between(-50000, 100000, line[i].y)) return 0;
	}
	return 1;
}

void refreshFromFile (const char* filename, unsigned char isPoly, Color color) {
	
	FILE* fp = fopen(filename, "r");

	ClippingWindow cw1 = setClippingWindow(scaleFactor*(100+left),scaleFactor*(200+left),scaleFactor*(200+up),scaleFactor*(100+up));
	double xScalingFactor = (1000 - 500) / ( (scaleFactor*(200+left)) - (scaleFactor*(100+left)) );
	double yScalingFactor = (550 - 50) / ( scaleFactor*((200+left)) - scaleFactor*((100+left)));
	double xTranslation = (( (scaleFactor*(200+left)) * 500) - ( (scaleFactor*(100+left)) * 1000)) / ( (scaleFactor*(200+left)) - (scaleFactor*(100+left)));
	double yTranslation = (( (scaleFactor*(200+up)) * 50) - ( (scaleFactor*(100+up)) * 550)) / ( (scaleFactor*(200+up)) - (scaleFactor*(100+up)) );	

	while(!feof(fp)){

		
		int nPoints;
		fscanf(fp, "%d", &nPoints);
		Point * points = malloc(nPoints * sizeof(Point));

		
		int j;
		for(j = 0 ; j < nPoints ; j++) fscanf(fp, "%d %d", &points[j].x, &points[j].y); 

		if (isPoly) drawPolygon(j,points,color,1);
		else drawPolyline(j,points,color,1);

		for (j = 0 ; j < (isPoly ? nPoints : nPoints - 1) ;j++){
			int lawan = (j+1);
			if (j == (nPoints-1)) lawan = 0;

			LineAnalysisResult lar1;
			//kasus khusus kalau menaik vertikal
			if ((points[j].x == points[lawan].x) && (points[lawan].y > points[j].y)) {
					lar1 = analyzeLine(points[lawan] , points[j], cw1);
			}
			else {
					lar1 = analyzeLine(points[j] , points[lawan], cw1);
			}
			Point clippedLine[2];
			clipLine(lar1,cw1,clippedLine);
			if (isLineSane(2, clippedLine)) {
				drawPolyline(2,clippedLine,setColor(255,0,0),1);
				ScaleLine(clippedLine,xScalingFactor,yScalingFactor);
				TranslationLine(clippedLine,xTranslation,yTranslation);
				drawPolyline(2,clippedLine,color,1);
			}
		}
		free(points);
	}
	close(fileno(fp));
}


//redraw framebuffer
void refreshScreen() 
{

	printBackground(setColor(0,0,0));

	Point clippingWindow[4];
	clippingWindow[0] = makePoint(scaleFactor*(100+left),scaleFactor*(100+up));
	clippingWindow[1] = makePoint(scaleFactor*(100+left),scaleFactor*(200+up));
	clippingWindow[2] = makePoint(scaleFactor*(200+left),scaleFactor*(200+up));
	clippingWindow[3] = makePoint(scaleFactor*(200+left),scaleFactor*(100+up));
	drawPolygon(4,clippingWindow,setColor(0,180,180),4);

	Point viewingWindow[4];
	viewingWindow[0] = makePoint(500,50);
	viewingWindow[1] = makePoint(500,550);
	viewingWindow[2] = makePoint(1000,550);
	viewingWindow[3] = makePoint(1000,50);
	drawPolygon(4,viewingWindow,setColor(0,255,180),1);

	if (drawBuildings) refreshFromFile("building.txt", 1, setColor(255,255,255));
	if (drawRoads) refreshFromFile("jalan.txt", 0,setColor(255,255,0));
	if (drawTrees) refreshFromFile("pohon.txt", 1,setColor(0,255,0));

}



//keypress listener in separate thread
void *keypressListen(void *x_void_ptr) {
	 int cmd = ' ';
	 while (1) 
	 {
	 	cmd = getch();
	 	if (cmd == LEFT_KEYPRESS) { left -= 20; refreshScreen();}
	    else if ( cmd == RIGHT_KEYPRESS) {	left+= 20;refreshScreen();	}
	    else if ( cmd == UP_KEYPRESS ) {up += 20; refreshScreen();}
	    else if ( cmd == DOWN_KEYPRESS ) {up -= 20; refreshScreen();}
	    else if ( cmd == ZOOMIN_KEYPRESS) {scaleFactor -= 0.1; refreshScreen();}
	    else if ( cmd == ZOOMOUT_KEYPRESS) {scaleFactor += 0.1; refreshScreen();}
	    else if ( cmd == TOGGLE_BUILDING_KEYPRESS) {drawBuildings = !drawBuildings; refreshScreen();}
	    else if ( cmd == TOGGLE_ROADS_KEYPRESS) {drawRoads = !drawRoads; refreshScreen();}
	    else if ( cmd == TOGGLE_TREES_KEYPRESS) {drawTrees = !drawTrees; refreshScreen();}
	}
	return NULL;
}

//prevents exiting program
void programBarrier(){
	while(1) {}
}

int main() {
	initScreen();
	printBackground(setColor(0,0,0));
	refreshScreen();
	pthread_create(&keypressListener, NULL, keypressListen, NULL);
	programBarrier();
	terminate();
	return 0;
}