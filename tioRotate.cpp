#include "framebuffer.h"
#include <iostream>
#include <string.h>

int main(void) {
	int jumlah = 3;
	FrameBuffer fb; 
	//fb.clearScreen();
	Polygon swapPoly;
	Polygon p[jumlah];
	p[0].addPoint(Point(100,100));
	p[0].addPoint(Point(100,200));
	p[0].addPoint(Point(200,100));
	p[0].addPoint(Point(200,200));
	p[0].setPriority(5);
	p[0].setColor(Color(100,100,100));

	p[1].addPoint(Point(100,100));
	p[1].addPoint(Point(150,100));
	p[1].addPoint(Point(150,150));
	p[1].addPoint(Point(100,150));
	p[1].setPriority(1);

	p[1].setColor(Color(10,100,0));

	p[2].addPoint(Point(100,100));
	p[2].addPoint(Point(130,100));
	p[2].addPoint(Point(130,130));
	p[2].addPoint(Point(100,130));
	p[2].setPriority(2);
	p[2].setColor(Color(10,10,100));


	
/*
	for (int i = 0; i < jumlah; ++i)
	{
		cout << p[i].getPriority()<< " ";
	}
	cout<<endl;
	*/
	//fb.drawPolygon(p[0], Color(100,0,0));
	fb.anticlip(p, jumlah);

}