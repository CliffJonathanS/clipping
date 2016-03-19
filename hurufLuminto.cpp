#include "framebuffer.h"
#include <iostream>
#include <string.h>
void Draw (char* huruf, int x, int y);

int main(void) {
	int jumlah = 3;
	FrameBuffer fb; 
	//fb.clearScreen();
	Polygon huruf[jumlah];
	//Angka 1
	/*huruf[0].addPoint(Point(4,1));
	huruf[0].addPoint(Point(5,1));
	huruf[0].addPoint(Point(5,17));
	huruf[0].addPoint(Point(4,17));
	huruf[0].setPriority(1);
	huruf[0].setColor(Color(200,200,200));*/

	//Angka 2
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,12));
	huruf[0].addPoint(Point(10,12));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(0,6));
	huruf[0].addPoint(Point(8,6));
	huruf[0].addPoint(Point(8,2));
	huruf[0].addPoint(Point(0,2));*/

	//Angka 3
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(0,12));
	huruf[0].addPoint(Point(8,12));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(0,8));
	huruf[0].addPoint(Point(0,6));
	huruf[0].addPoint(Point(8,6));
	huruf[0].addPoint(Point(8,2));
	huruf[0].addPoint(Point(0,2));*/

	//Angka 4
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(8,6));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(0,8));*/

	//Angka 5
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(2,2));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(10,6));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(0,12));
	huruf[0].addPoint(Point(8,12));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(0,8));*/

	//Angka 6
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(2,2));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(10,6));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(Color(200,200,200));
	huruf[1].addPoint(Point(2,8));
	huruf[1].addPoint(Point(8,8));
	huruf[1].addPoint(Point(8,12));
	huruf[1].addPoint(Point(2,12));
	huruf[1].setPriority(1);
	huruf[0].setColor(Color(0,0,0));*/

	//Angka 7
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(8,2));
	huruf[0].addPoint(Point(0,2));*/

	huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(8,2));
	huruf[1].addPoint(Point(8,6));
	huruf[1].addPoint(Point(2,6));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);

	huruf[2].addPoint(Point(2,8));
	huruf[2].addPoint(Point(8,8));
	huruf[2].addPoint(Point(8,12));
	huruf[2].addPoint(Point(2,12));
	huruf[2].setPriority(1);
	huruf[2].setColor(0,0,0);	
	
	fb.anticlip(huruf, jumlah);

	
/*
	for (int i = 0; i < jumlah; ++i)
	{
		cout << p[i].getPriority()<< " ";
	}
	cout<<endl;
	*/
	//fb.drawPolygon(p[0], Color(100,0,0));
	//fb.anticlip(p, jumlah);

}