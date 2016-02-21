#include "framebuffer.h"
#include <iostream>

using namespace std;

int main() {
	FrameBuffer fb;
	fb.clearScreen();
	Polygon jawa;
	jawa.addPoint(Point(400,410));
	jawa.addPoint(Point(440,415));
	jawa.addPoint(Point(450,422));
	jawa.addPoint(Point(480,422));
	jawa.addPoint(Point(485,410));
	jawa.addPoint(Point(525,415));
	jawa.addPoint(Point(532,425));
	jawa.addPoint(Point(565,425));
	jawa.addPoint(Point(565,450));
	jawa.addPoint(Point(532,445));
	jawa.addPoint(Point(485,447));
	jawa.addPoint(Point(470,440));
	jawa.addPoint(Point(445,440));
	jawa.addPoint(Point(443,445));
	jawa.addPoint(Point(405,435));
	jawa.addPoint(Point(408,427));
	jawa.addPoint(Point(395,425));
	fb.drawPolygon(jawa, Color(60,200,80));
	fb.fillPolygon(jawa, Color(60,200,80));
	return 0;
}