#include "grafika.h"
#include "math.h"
#define IS_COMPLETELY_INSIDE 1
#define IS_COMPLETELY_OUTSIDE 2
#define	IS_INTERSECT 3
#define BOTHZERO 4
#define BOTHONE 5
#define ONEZERO 6

typedef struct
{
	int xLeft;
	int xRight;
	int yTop;
	int yBottom;
} ClippingWindow;

ClippingWindow setClippingWindow(int left, int right, int top, int bottom){
	ClippingWindow temp;
	temp.xLeft = left;
	temp.xRight = right;
	temp.yTop = top;
	temp.yBottom = bottom;
	return temp;
}


typedef struct
{
	int left;
	int right;
	int top;
	int bottom;

} RegionCode;

typedef struct
{
	int resultStatusCode;
	int isLeftIntersection;
	int isRightIntersection;
	int isTopIntersection;
	int isBottomIntersection;

	int isStartPointCompletelyInside;
	int isEndPointCompletelyInside;

	Point startPoint;
	Point endPoint;

	RegionCode startPointRegionCode;
	RegionCode endPointRegionCode;

} LineAnalysisResult;

LineAnalysisResult initLineAnalysisResult() {
	LineAnalysisResult temp;
	temp.resultStatusCode = 0;
	temp.isBottomIntersection = 0;
	temp.isRightIntersection = 0;
	temp.isTopIntersection = 0;
	temp.isTopIntersection = 0;
	return temp;
}



void printRegionCode(RegionCode rc){
	printf("%d %d %d %d ---", rc.top, rc.bottom,rc.right, rc.left);
}

RegionCode initRegionCode(){
	RegionCode temp;
	temp.left = 0;
	temp.right = 0;
	temp.top = 0;
	temp.bottom = 0;
	return temp;
}

int checkRegionCodeBit(int a, int b){
	if (a == 0) {
		if (b == 0) return BOTHZERO;
		return ONEZERO;
	}
	else if (a == 1) {
		if (b == 1) return BOTHONE;
		return ONEZERO;
	}
}

RegionCode computeRegionCode(Point p, ClippingWindow cw){
	RegionCode temp =  initRegionCode();

	if (p.x < cw.xLeft) temp.left = 1;
	if (p.x > cw.xRight) temp.right = 1;
	if (p.y > cw.yTop) temp.top = 1;
	if (p.y < cw.yBottom) temp.bottom = 1;

	return temp;
}

int isPointCompletelyInside(RegionCode x) {
	return ((x.top == 0) && (x.left == 0) && (x.right == 0) && (x.bottom == 0));
}

int isCompletelyInside(LineAnalysisResult x){
	return ((x.isTopIntersection == BOTHZERO) && (x.isLeftIntersection == BOTHZERO) && (x.isRightIntersection == BOTHZERO) && (x.isBottomIntersection == BOTHZERO));
}

int isCompletelyOutside(LineAnalysisResult x){
	return ((x.isBottomIntersection == BOTHONE) || (x.isTopIntersection == BOTHONE) || (x.isLeftIntersection == BOTHONE) || (x.isRightIntersection == BOTHONE));
}



LineAnalysisResult analyzeLine(Point startPoint, Point endPoint, ClippingWindow cw){
	RegionCode startPointRegionCode = computeRegionCode(startPoint,cw);
	RegionCode endPointRegionCode = computeRegionCode(endPoint,cw);

	LineAnalysisResult result;
	result.isTopIntersection = checkRegionCodeBit(startPointRegionCode.top, endPointRegionCode.top);
	result.isBottomIntersection = checkRegionCodeBit(startPointRegionCode.bottom , endPointRegionCode.bottom);
	result.isLeftIntersection = checkRegionCodeBit(startPointRegionCode.left, endPointRegionCode.left);
	result.isRightIntersection = checkRegionCodeBit(startPointRegionCode.right , endPointRegionCode.right);

	result.isStartPointCompletelyInside = isPointCompletelyInside(startPointRegionCode);
	result.isEndPointCompletelyInside = isPointCompletelyInside(endPointRegionCode);

	result.startPoint = startPoint;
	result.endPoint = endPoint;

	result.startPointRegionCode = startPointRegionCode;
	result.endPointRegionCode = endPointRegionCode;

	return result;
}



void clipLine(LineAnalysisResult lar1, ClippingWindow cw1 , Point * output) {

	Color white = setColor(255,255,255);
	Point line[2];
	line[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
	line[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);

	if (isCompletelyInside(lar1)) {
		drawPolygon(2,line,white,1);
		output[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
		output[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);
	 }
	else if (isCompletelyOutside(lar1)) {
		output[0] = makePoint(0 , 0);
		output[1] = makePoint(0, 0);
	}
	else
	{

		//top intersection
		if( lar1.isTopIntersection == ONEZERO) {
			//start point adjust
			if(lar1.startPointRegionCode.top) {
				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.startPoint.y = cw1.yTop;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.startPoint.x + ((cw1.yTop - lar1.startPoint.y) / m);
					lar1.startPoint.x = round(newX);
					lar1.startPoint.y = cw1.yTop;
				}
				if ((lar1.startPoint.x >= cw1.xLeft) && (lar1.startPoint.x <= cw1.xRight)) {
					lar1.startPointRegionCode = initRegionCode();
				}
			}

			//end point adjust
			if(lar1.endPointRegionCode.top) {
				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.startPoint.y = cw1.yTop;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.endPoint.x + ((cw1.yTop - lar1.endPoint.y) / m);
					lar1.endPoint.x = round(newX);
					lar1.endPoint.y = cw1.yTop;
				}
				if ((lar1.endPoint.x >= cw1.xLeft) && (lar1.endPoint.x <= cw1.xRight)){
					lar1.endPointRegionCode = initRegionCode();
				}
			}
		}


		//bottom slice
		if( lar1.isBottomIntersection == ONEZERO) {
			//start point adjust
			if(lar1.startPointRegionCode.bottom) {
				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.startPoint.y = cw1.yBottom;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.startPoint.x + ((cw1.yBottom - lar1.startPoint.y) / m);
					lar1.startPoint.x = round(newX);
					lar1.startPoint.y = cw1.yBottom;
				}
				if ((lar1.startPoint.x >= cw1.xLeft) && (lar1.startPoint.x <= cw1.xRight)){
					lar1.startPointRegionCode = initRegionCode();
				}
			}

			//end point adjust
			if(lar1.endPointRegionCode.bottom) {

				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.endPoint.y = cw1.yBottom;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.endPoint.x + ( (cw1.yBottom - lar1.endPoint.y) / m);
					lar1.endPoint.x = round(newX);
					lar1.endPoint.y = cw1.yBottom;
				}
				if ((lar1.endPoint.x >= cw1.xLeft) && (lar1.endPoint.x <= cw1.xRight)){
					lar1.endPointRegionCode = initRegionCode();
				}
			}
		}



		//left slice
		if ( lar1.isLeftIntersection == ONEZERO) {

			//start point adjust
			if(lar1.startPointRegionCode.left) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.startPoint.y +  (m *((double) cw1.xLeft - (double) lar1.startPoint.x));
				lar1.startPoint.x = cw1.xLeft;
				lar1.startPoint.y = round(newY);
				if ((lar1.startPoint.x >= cw1.yBottom) && (lar1.startPoint.x <= cw1.yTop)){
					lar1.startPointRegionCode = initRegionCode();
				}
			}

			//end point adjust
			if(lar1.endPointRegionCode.left) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.endPoint.y +  (m *( (double) cw1.xLeft - (double) lar1.endPoint.x ));
				lar1.endPoint.x = cw1.xLeft;
				lar1.endPoint.y = round(newY);
				if ((lar1.endPoint.x >= cw1.yBottom) && (lar1.endPoint.x <= cw1.yTop)){
					lar1.endPointRegionCode = initRegionCode();
				}
			}
		}


		//right slice
		if ( lar1.isRightIntersection == ONEZERO) {
			//start point adjust
			if(lar1.startPointRegionCode.right) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.startPoint.y +  (m *((double)cw1.xRight - (double)lar1.startPoint.x ));
				lar1.startPoint.x = cw1.xRight;
				lar1.startPoint.y = round(newY);

			}

			//end point adjust
			if(lar1.endPointRegionCode.right) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.endPoint.y +  (m *((double) cw1.xRight -(double) lar1.endPoint.x  ));
				lar1.endPoint.x = cw1.xRight;
				lar1.endPoint.y = round(newY);
			}
		}

		line[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
		line[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);
		output[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
		output[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);

		/*
		Color red = setColor(255,0,0);
		drawPolygon(2,line,setColor(0,0,0),1);
		drawPolygon(2,line,red,1);
		*/

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


double left;
double up;
double scaleFactor;
unsigned char drawBuildings = 1;
unsigned char drawRoads = 1;
unsigned char drawTrees = 1;

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
	//clip
	ClippingWindow cw1 = setClippingWindow(scaleFactor*(100+left),scaleFactor*(200+left),scaleFactor*(200+up),scaleFactor*(100+up));

	double xScalingFactor = (1000 - 500) / ( (scaleFactor*(200+left)) - (scaleFactor*(100+left)) );
	double yScalingFactor = (550 - 50) / ( scaleFactor*((200+left)) - scaleFactor*((100+left)));
	double xTranslation = (( (scaleFactor*(200+left)) * 500) - ( (scaleFactor*(100+left)) * 1000)) / ( (scaleFactor*(200+left)) - (scaleFactor*(100+left)));
	double yTranslation = (( (scaleFactor*(200+up)) * 50) - ( (scaleFactor*(100+up)) * 550)) / ( (scaleFactor*(200+up)) - (scaleFactor*(100+up)) );

	FILE* fp;
	int i;
	fp = fopen(filename, "r");

	while(!feof(fp)){
		fscanf(fp, "%d", &i);

		Point * points = malloc(i * sizeof(Point));
		int j;
		for(j = 0 ; j < i ; j++){
			fscanf(fp, "%d %d", &points[j].x, &points[j].y);
			//printf("Point %d : %d %d \n", j , points[j].x , points[j].y);
		}

		if (isPoly) drawPolygon(j,points,color,1);
		else drawPolyline(j,points,color,1);


		for(j = 0 ; j < (isPoly ? i : i - 1) ;j++){
			int lawan = (j+1);
			if (j == (i-1)) lawan = 0;

			LineAnalysisResult lar1;
			//kasus khusus kalau menaik vertikal
			if ((points[j].x == points[lawan].x) && (points[lawan].y > points[j].y)) {
					lar1 = analyzeLine(points[lawan] , points[j], cw1);
			}
			else {
					lar1 = analyzeLine(points[j] , points[lawan], cw1);
			}
			Point clippedLine1[2];
			clipLine(lar1,cw1,clippedLine1);
			if (isLineSane(2, clippedLine1)) {
				drawPolyline(2,clippedLine1,setColor(255,0,0),1);
				ScaleLine(clippedLine1,xScalingFactor,yScalingFactor);
				TranslationLine(clippedLine1,xTranslation,yTranslation);
				drawPolyline(2,clippedLine1,color,1);
			}
		}


		free(points);
	}
	close(fileno(fp));

}

void refreshScreen() {
	Color bgColor = setColor(0,0,0);
	Color white = setColor(255,255,255);
	printBackground(bgColor);

	//draw clipping window
	Point clippingWindow_v[4];
	clippingWindow_v[0] = makePoint(scaleFactor*(100+left),scaleFactor*(100+up));
	clippingWindow_v[1] = makePoint(scaleFactor*(100+left),scaleFactor*(200+up));
	clippingWindow_v[2] = makePoint(scaleFactor*(200+left),scaleFactor*(200+up));
	clippingWindow_v[3] = makePoint(scaleFactor*(200+left),scaleFactor*(100+up));
	drawPolygon(4,clippingWindow_v,setColor(0,180,180),4);

	//draw viewing window
	Point viewingWindow[4];
	viewingWindow[0] = makePoint(500,50);
	viewingWindow[1] = makePoint(500,550);
	viewingWindow[2] = makePoint(1000,550);
	viewingWindow[3] = makePoint(1000,50);
	drawPolygon(4,viewingWindow,setColor(0,255,180),1);

	if (drawBuildings) refreshFromFile("albar.txt", 1, setColor(255,255,255));
	if (drawRoads) refreshFromFile("jalan.txt", 0,setColor(255,255,0));
	if (drawTrees) refreshFromFile("pohon.txt", 1,setColor(0,255,0));

}



/* this function is run by the second thread */
void *keypressListen(void *x_void_ptr) {
	 int cmd = ' ';
	 while (1) {
	 	cmd = getch();
	 	if (cmd == ENTER_KEYPRESS) { }
    else if (cmd == LEFT_KEYPRESS) { left -= 20; refreshScreen();}
    else if (cmd == RIGHT_KEYPRESS) {	left+= 20;refreshScreen();	}
    else if ( cmd == UP_KEYPRESS ) {up += 20; refreshScreen();}
    else if (cmd == DOWN_KEYPRESS ) {up -= 20; refreshScreen();}
    else if ( cmd == ZOOMIN_KEYPRESS) {scaleFactor -= 0.1; refreshScreen();}
    else if ( cmd == ZOOMOUT_KEYPRESS) {scaleFactor += 0.1; refreshScreen();}
    else if ( cmd == 122) {drawBuildings = !drawBuildings; refreshScreen();}
    else if ( cmd == 120) {drawRoads = !drawRoads; refreshScreen();}
    else if ( cmd == 99) {drawTrees = !drawTrees; refreshScreen();}
	}
	return NULL;
}



int main() {
	left = 0;
	up = 0;
	scaleFactor = 1;



	initScreen();
	printBackground(setColor(0,0,0));
	refreshScreen();




	//keypress
 	pthread_t keypressListener;
	if(pthread_create(&keypressListener, NULL, keypressListen, NULL)) {
		fprintf(stderr, "Error creating threasd\n");
		return 1;
	}

	refreshScreen();

	while(1){
		usleep(1000000);
	}




	terminate();
	return 0;
}
