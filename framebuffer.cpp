#include "framebuffer.h"
#include <iostream>

using namespace std;

Color::Color(int r, int g, int b) {
	R = r;
	G = g;
	B = g;
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



Polygon::Polygon() {

}
Polygon::Polygon(const Polygon& polygon) {
	for (int i=0;i<polygon.points.size();i++) {
		points.push_back(polygon.points[i]);
	}
}
Polygon::~Polygon() {
	points.clear();
}

// getter
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

// setter
void Polygon::setPoint(int i, Point point){
	// asumsi 1 < size
	points[i] = point;
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
	for (i=0;i<getScreenHeight();i++) {
		for (j=0;j<getScreenWidth();j++) {
			drawPoint(Point(j, i), Color(0,0,0));
		}
	}
}
void FrameBuffer::drawPoint(Point point, Color color){
	long location;
	int drawx = point.getX();
	int drawy = point.getY();

	if ((drawx < getScreenWidth()) && (drawy < getScreenHeight()) && (drawx >= 0) && (drawy >= 0)) {
		location = (drawx+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (drawy+vinfo.yoffset) * finfo.line_length;
		*((uint32_t*)(display + location)) = (color.getR()<<vinfo.red.offset) | (color.getG()<<vinfo.green.offset) | (color.getB()<<vinfo.blue.offset);
	}
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
void FrameBuffer::drawPolygon(Polygon polygon, Color color){
	int i;
	for (i=0;i<polygon.getPoints().size()-1;i++) {
		drawLine(polygon.getPoints().at(i), polygon.getPoints().at(i+1), color);
	}
	drawLine(polygon.getPoints().at(polygon.getPoints().size()-1), polygon.getPoints().at(0), color);
}
void FrameBuffer::fillPolygon(Polygon polygon, Color color){
	int  nodes, *nodeX, drawx, drawy, i, j, swap ;
	nodeX = (int*) malloc (sizeof(int) * polygon.getPoints().size());
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
				for (drawx=nodeX[i]; drawx<nodeX[i+1]; drawx++) drawPoint(Point(drawx,drawy), color);
			}
		}
	}

}