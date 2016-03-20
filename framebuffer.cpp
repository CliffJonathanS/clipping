#include "framebuffer.h"
#include <iostream>
#include "math.h"
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

#define LEFTWINDOW 0
#define RIGHTWINDOW 300
#define UPWINDOW 0
#define DOWNWINDOW 300

//untuk clipping
typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
static char NormalScanline[RIGHTWINDOW][DOWNWINDOW];

Color::Color() {
	R=0; G=0; B=0;
}

Color::Color(int r, int g, int b) {
	R = r;
	G = g;
	B = b;
}
Color::Color(const Color& color) {
	R = color.R;
	G = color.G;
	B = color.B;
}
Color::~Color() {
	
}

// getter
int Color::getR() {
	return R;
}
int Color::getG() {
	return G;
}
int Color::getB(){
	return B;
}

// setter
void Color::setR(int r){
	R = r;
}
void Color::setG(int g){
	G = g;
}
void Color::setB(int b){
	B = b;
}

// operator=
Color& Color::operator=(const Color& color){
	R = color.R;
	G = color.G;
	B = color.B;
	return *this;
}



Point::Point(float x, float y) {
	X = x;
	Y = y;
}
Point::Point(const Point& point) {
	X = point.X;
	Y = point.Y;
}
Point::~Point() {
	
}

// getter
float Point::getX(){
	return X;
}
float Point::getY(){	
	return Y;
}

// setter
void Point::setX(float x){
	X = x;
}
void Point::setY(float y){
	Y = y;
}

// operator=
Point& Point::operator=(const Point& point){
	X = point.X;
	Y = point.Y;
	return *this;
}

// Rotate
Point& Point::rotate(float angle, Point pusat){
	//printf("angle %f, pusat x %f, pusat y %f, cos %f, sin %f\n", angle, this->X, this->Y , cos(angle), sin(angle));
	float tempX = this->X;
	float tempY = this->Y;
	this->X = (cos(angle) * (tempX - pusat.X)) - (sin(angle) * (tempY - pusat.Y)) + pusat.X;
	
	this->Y = (sin(angle) * (tempX - pusat.X)) + (cos(angle) * (tempY - pusat.Y)) + pusat.Y;
	return *this;
}


Polygon::Polygon() {

}
Polygon::Polygon(const Polygon& polygon, int _priority) {
	for (int i=0;i<polygon.points.size();i++) {
		points.push_back(polygon.points[i]);
	}
	priority = _priority;
	pcolor = Color(0,0,0);

}
Polygon::~Polygon() {
	points.clear();
}

// getter
int Polygon::getPriority(){
	return priority;
}
Point Polygon::getPoint(int i){
	// asumsi i < size
	return points[i];
}
vector<Point> Polygon::getPoints() {
	return points;
}
float Polygon::getLeft() {
	int i;
	Point ret = points.front();
	for (i=1;i<points.size();i++) {
		if (points[i].getX() < ret.getX())
			ret = points[i];
	}
	return ret.getX();
}
float Polygon::getRight() {
	int i;
	Point ret = points.front();
	for (i=1;i<points.size();i++) {
		if (points[i].getX() > ret.getX())
			ret = points[i];
	}
	return ret.getX();
}
float Polygon::getTop() {
	int i;
	Point ret = points.front();
	for (i=1;i<points.size();i++) {
		if (points[i].getY() < ret.getY())
			ret = points[i];
	}
	return ret.getY();
}
float Polygon::getBottom() {
	int i;
	Point ret = points.front();
	for (i=1;i<points.size();i++) {
		if (points[i].getY() > ret.getY())
			ret = points[i];
	}
	return ret.getY();
}

Color Polygon::getColor(){
	return pcolor;
}

// setter
void Polygon::setPriority(int i){
	priority = i;
}
void Polygon::setPoint(int i, Point point){
	// asumsi 1 < size
	points[i] = point;
}

void Polygon::setColor(Color color){
	pcolor = color;
}
// method
void Polygon::addPoint(Point point) {
	points.push_back(point);
}

// operator=
Polygon& Polygon::operator=(const Polygon& polygon){
	points.clear();
	for (int i=0;i<polygon.points.size();i++) {
		points.push_back(polygon.points[i]);
	}
	priority = polygon.priority;
	pcolor = polygon.pcolor;
	return *this;
}

FrameBuffer::FrameBuffer() {
	//open file descriptor and get info
	fdScreen = open( "/dev/fb0", O_RDWR );

	ioctl( fdScreen, FBIOGET_VSCREENINFO, &vinfo);
	ioctl( fdScreen, FBIOGET_FSCREENINFO, &finfo);

	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	//get writable screen memory
	display = (char *)mmap( 0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fdScreen, 0 );
}
FrameBuffer::~FrameBuffer() {
	munmap(display, screensize);
	close(fdScreen);
}

// getter
int FrameBuffer::getScreenWidth(){
	return vinfo.xres;
}
int FrameBuffer::getScreenHeight(){
	return vinfo.yres;
}

// methods
void FrameBuffer::clearScreen(){
	int i, j;
	for (i=0;i<getScreenHeight()-10;i++) {
		for (j=0;j<getScreenWidth()-10;j++) {
			drawPoint(Point(j, i), Color(0,0,0));
		}
	}
}
void FrameBuffer::drawPoint(Point point, Color color){
	long location;
	int drawx = point.getX();
	int drawy = point.getY();

	if ((drawx < getScreenWidth()-7) && (drawy < getScreenHeight()-7) && (drawx >= 0) && (drawy >= 0)) {
		location = (drawx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (drawy+vinfo.yoffset) * finfo.line_length;
		*((uint32_t*)(display + location)) = (color.getR()<<vinfo.red.offset) | (color.getG()<<vinfo.green.offset) | (color.getB()<<vinfo.blue.offset);
	}
}


bool FrameBuffer::clipPoint(Point point){
	int drawx = point.getX();
	int drawy = point.getY();

	if ((drawx < RIGHTWINDOW) && (drawy < DOWNWINDOW) && (drawx >= LEFTWINDOW) && (drawy >= UPWINDOW)) {
		return true;
	}
	return false;
}
void FrameBuffer::drawLine(Point p1, Point p2, Color color){
	int x1 = p1.getX();
	int x2 = p2.getX();
	int y1 = p1.getY();
	int y2 = p2.getY();

	int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
	int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	while(1){
			drawPoint(Point(x1,y1), color);		
		
		if (x1==x2 && y1==y2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
	}
}

void FrameBuffer::drawCurve(Point* points, int n, Color color) {
	float k;
    for (k=0;k<1;k+=0.001) {
    	int i, j;
	    float t = k;
	    Point* temp = (Point*) malloc (sizeof(Point) * n);
	    for (i=0;i<n;i++) {
	    	temp[i] = points[i];
	    }
	    i = n - 1;
	    while (i > 0) {
	        for (j = 0;j<i;j++) {
	            temp[j].setX(temp[j].getX() + t * (temp[j+1].getX() - temp[j].getX()));
	            temp[j].setY(temp[j].getY() + t * (temp[j+1].getY() - temp[j].getY()));
	        }
	        i--;
	    }
	    Point ret = temp[0];
	    //delete[] temp;
	    drawPoint(ret, color);
	}
}

// referensi : https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
OutCode ComputeOutCode(Point p)
{
	float x= p.getX();
	float y= p.getY();
	OutCode code;

	code = INSIDE;          // initialised as being inside of clip window

	if (x < LEFTWINDOW)           // to the left of clip window
		code |= LEFT;
	else if (x > RIGHTWINDOW)      // to the right of clip window
		code |= RIGHT;
	if (y > DOWNWINDOW)           // below the clip window
		code |= BOTTOM;
	else if (y < UPWINDOW)      // above the clip window
		code |= TOP;

	return code;
}
// referensi : https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
void FrameBuffer::CohenSutherlandLineClipAndDraw(Point p1, Point p2, Color color){
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(p1);
	OutCode outcode1 = ComputeOutCode(p2);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			float x, y;
			float x0=p1.getX();

			float x1=p2.getX();

			float y0=p1.getY();

			float y1=p2.getY();
			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (UPWINDOW - y0) / (y1 - y0);
				y = UPWINDOW;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (DOWNWINDOW - y0) / (y1 - y0);
				y = DOWNWINDOW;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (RIGHTWINDOW - x0) / (x1 - x0);
				x = RIGHTWINDOW;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (LEFTWINDOW - x0) / (x1 - x0);
				x = LEFTWINDOW;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				p1.setX(x);
				p1.setY(y);
				outcode0 = ComputeOutCode(p1);
			} else {
				p2.setX(x);
				p2.setY(y);
				outcode1 = ComputeOutCode(p2);
			}
		}
	}
	if (accept) {
               // Following functions are left for implementation by user based on
               // their platform (OpenGL/graphics.h etc.)
               drawLine(p1,p2,color);
	}
}

void FrameBuffer::drawPolygon(Polygon polygon, Color color){
	int i;
	for (i=0;i<polygon.getPoints().size()-1;i++) {
		drawLine(polygon.getPoints().at(i), polygon.getPoints().at(i+1), color);
	}
	drawLine(polygon.getPoints().at(polygon.getPoints().size()-1), polygon.getPoints().at(0), color);
}

void FrameBuffer::drawRectangle(int x, int y, Color color, int SIZE, vector<Polygon>& vec ){
	Polygon rectangle;
		rectangle.addPoint(Point(x,y));
		rectangle.addPoint(Point(x+SIZE,y));
		rectangle.addPoint(Point(x+SIZE,y+SIZE));
		rectangle.addPoint(Point(x,y+SIZE));
		rectangle.setColor(color);
		rectangle.setPriority(4);
		vec.push_back(rectangle);

}
void FrameBuffer::fillPolygon(Polygon polygon, Color color){
	int  nodes, *nodeX, drawx, drawy, i, j, swap ;
	nodeX = (int*) malloc (sizeof(int*) * polygon.getPoints().size());
	//  Loop through the rows of the image.
	for (drawy=polygon.getTop(); drawy<polygon.getBottom(); drawy++) {
		//  Build a list of nodes.
		nodes=0; j=polygon.getPoints().size()-1;
		for (i=0; i<polygon.getPoints().size(); i++) {
			if (polygon.getPoints().at(i).getY()<(double) drawy && polygon.getPoints().at(j).getY()>=(double) drawy ||  polygon.getPoints().at(j).getY()<(double) drawy && polygon.getPoints().at(i).getY()>=(double) drawy) {
				nodeX[nodes++]=(int) (polygon.getPoints().at(i).getX()+(drawy-polygon.getPoints().at(i).getY())/(polygon.getPoints().at(j).getY()-polygon.getPoints().at(i).getY())*(polygon.getPoints().at(j).getX()-polygon.getPoints().at(i).getX()));
			}
			j=i;
		}
		//  Sort the nodes, via a simple “Bubble” sort.
		i=0;
		while (i<nodes-1) {
			if (nodeX[i]>nodeX[i+1]) {
				swap=nodeX[i]; 
				nodeX[i]=nodeX[i+1]; 
				nodeX[i+1]=swap; 
				if (i) i--;
			}
			else
				i++; 
		}
		
		//  Fill the pixels between node pairs.
		for (i=0; i<nodes; i+=2) {
			if   (nodeX[i  ]>=polygon.getRight()) break;
			if   (nodeX[i+1]> polygon.getLeft() ) {
				if (nodeX[i  ]< polygon.getLeft() ) nodeX[i  ]=polygon.getLeft() ;
				if (nodeX[i+1]> polygon.getRight()) nodeX[i+1]=polygon.getRight();
				for (drawx=nodeX[i]; drawx<nodeX[i+1]; drawx++){
					if (clipPoint(Point(drawx,drawy))){
						drawPoint(Point(drawx,drawy), color);
					}
					//printf("%d,%d\n",drawx, drawy );	
				} 
			}
		}
	}

}

vector<Polygon> FrameBuffer::polygonparser(){
	string line;
	vector<Polygon> vpol;
	ifstream myfile ("example.txt");
		if (myfile.is_open())
		{
		    while ( getline (myfile,line) )
		    {
		    	Polygon polygon;
			    replace( line.begin(), line.end(), ',', ' ');
			    stringstream ss(line);
			    	int priority, r,g,b; 
			    	ss >> priority;
			    	ss >> r;
			    	ss >> g;
			    	ss >> b;
			    	polygon.setPriority(priority);
			    	polygon.setColor(Color(r,g,b));
			    while (ss.good()){
			    	float tempx,tempy;
				    ss >> tempx;
				    ss >> tempy;
				    polygon.addPoint(Point(tempx,tempy+20));
				}
				vpol.push_back(polygon);

		    }
		    myfile.close();
	  	}
	 return vpol;
}

void FrameBuffer::addpolygonsfinal(string s, Point p, vector<Polygon>& vec){
	int offsetX = p.getX();
	for(int i=0;i<s.length();i++){
		//printf("Huruf %c\n", s.at(i));
		string line;
		ifstream myfile ("definisi.txt");
		if (myfile.is_open())
		{
		    while ( getline (myfile,line) )
		    {
		    	//printf("Dalam file %c\n", line.at(0));
		    	if (s.at(i)==line.at(0)){
		    		getline(myfile,line);
		    		do{		    			
		    			if((int)line.find(',')>=0){
		    				Polygon polygon;
						    replace( line.begin(), line.end(), ',', ' ');
						    stringstream ss(line);
						    	int priority, r,g,b; 
						    	ss >> priority;
						    	ss >> r;
						    	ss >> g;
						    	ss >> b;
						    	polygon.setPriority(priority);
						    	polygon.setColor(Color(r,g,b));
						    while (ss.good()){
						    	float tempx,tempy;
							    ss >> tempx;
							    ss >> tempy;
							    polygon.addPoint(Point(tempx+offsetX,tempy+p.getY()));
							    
							}
							vec.push_back(polygon);

		    			}
		    			getline(myfile,line);
		    		} while ((int)line.find(',')>=0);

		    		offsetX += 10;
		    		break;
		    	}
		    }
		    myfile.close();
	  	}
		
	}
}

bool FrameBuffer::isText(int priority){
	return priority >=5 ;
}

void FrameBuffer::anticlip(vector<Polygon> polygon, vector<char> toogleMenu){
	int  nodes, *nodeX, drawx, drawy, i, j, swap,l, temp ;
	Polygon swapPoly;
	int jumlah = polygon.size();
	memset(NormalScanline, 0, RIGHTWINDOW * DOWNWINDOW);
	//  Sort based on priority. High integer priority will be drawn first
	
	for(i=0; i< (jumlah - 1); ++i)
	{
		for(j = i + 1; j > 0; --j)
		{
			if(polygon.at(j).getPriority() > polygon.at(j-1).getPriority())
			{
			//Swaps the values
				swapPoly=polygon.at(j); 
				polygon.at(j)=polygon.at(j-1); 
				polygon.at(j-1)=swapPoly; 
			}
		}
	}


	
	for (l = 0; l < jumlah; l++) {

		nodeX = (int*) malloc (sizeof(int) * polygon.at(l).getPoints().size());
		for (drawy=polygon.at(l).getTop(); drawy<polygon.at(l).getBottom(); drawy++) {
			//  Build a list of nodes.
			nodes=0; j=polygon.at(l).getPoints().size()-1;
			for (i=0; i<polygon.at(l).getPoints().size(); i++) {
				if (polygon.at(l).getPoints().at(i).getY()<(double) drawy && polygon.at(l).getPoints().at(j).getY()>=(double) drawy ||  polygon.at(l).getPoints().at(j).getY()<(double) drawy && polygon.at(l).getPoints().at(i).getY()>=(double) drawy) {
					nodeX[nodes++]=(int) (polygon.at(l).getPoints().at(i).getX()+(drawy-polygon.at(l).getPoints().at(i).getY())/(polygon.at(l).getPoints().at(j).getY()-polygon.at(l).getPoints().at(i).getY())*(polygon.at(l).getPoints().at(j).getX()-polygon.at(l).getPoints().at(i).getX()));
				}
				j=i;
			}
			//  Sort the nodes, via a simple “Bubble” sort.
			i=0;
			while (i<nodes-1) {
				if (nodeX[i]>nodeX[i+1]) {
					swap=nodeX[i]; 
					nodeX[i]=nodeX[i+1]; 
					nodeX[i+1]=swap; 
					if (i) i--;
				}
				else
					i++; 
			}
			
			//  Fill the pixels between node pairs.
			for (i=0; i<nodes; i+=2) {
				if   (nodeX[i  ]>=polygon.at(l).getRight()) break;
				if   (nodeX[i+1]> polygon.at(l).getLeft() ) {
					if (nodeX[i  ]< polygon.at(l).getLeft() ) nodeX[i  ]=polygon.at(l).getLeft() ;
					if (nodeX[i+1]> polygon.at(l).getRight()) nodeX[i+1]=polygon.at(l).getRight();
					for (drawx=nodeX[i]; drawx<nodeX[i+1]; drawx++){
						if (clipPoint(Point(drawx,drawy))){
							//case for non text
							//if(find(toogleMenu.begin(), toogleMenu.end(), polygon.at(l).getPriority()) != 5){
								if (NormalScanline[drawy][drawx] == 0 && (find(toogleMenu.begin(), toogleMenu.end(), polygon.at(l).getPriority()) != toogleMenu.end())) {
									NormalScanline[drawy][drawx] = 1;
									drawPoint(Point(drawx,drawy), polygon.at(l).getColor());	
								}
						}
						//printf("%d,%d\n",drawx, drawy );	
					}
				}
			}


			
		}

	}
	memset(NormalScanline, 0, RIGHTWINDOW * DOWNWINDOW);


}