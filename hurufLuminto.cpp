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
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(8,2));
	huruf[0].addPoint(Point(0,2));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Angka 8
	/*huruf[0].addPoint(Point(0,0));
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
	huruf[2].setColor(0,0,0);	*/

	//Angka 9
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(0,8));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(8,2));
	huruf[1].addPoint(Point(8,6));
	huruf[1].addPoint(Point(2,6));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);*/

	//Angka 0
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(8,2));
	huruf[1].addPoint(Point(8,12));
	huruf[1].addPoint(Point(2,12));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);*/

	//Huruf A
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(8,2));
	huruf[1].addPoint(Point(8,6));
	huruf[1].addPoint(Point(2,6));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);*/
	
	//Huruf B
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,3));
	huruf[0].addPoint(Point(8,6));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(10,11));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,1));
	huruf[1].addPoint(Point(6,1));
	huruf[1].addPoint(Point(6,7));
	huruf[1].addPoint(Point(2,7));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);
	huruf[2].addPoint(Point(2,7));
	huruf[2].addPoint(Point(6,7));
	huruf[2].addPoint(Point(6,13));
	huruf[2].addPoint(Point(2,13));
	huruf[2].setPriority(1);
	huruf[2].setColor(0,0,0);*/

	//Huruf C
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(2,2));
	huruf[0].addPoint(Point(2,11));
	huruf[0].addPoint(Point(10,11));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Huruf D
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,7));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(6,2));
	huruf[1].addPoint(Point(8,7));
	huruf[1].addPoint(Point(6,12));
	huruf[1].addPoint(Point(2,12));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);*/
	
	//Huruf E
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(2,2));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(10,6));
	huruf[0].addPoint(Point(10,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,11));
	huruf[0].addPoint(Point(10,11));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf F
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(2,2));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(10,6));
	huruf[0].addPoint(Point(10,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf G
	/*huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,4));
	huruf[0].addPoint(Point(8,4));
	huruf[0].addPoint(Point(6,2));
	huruf[0].addPoint(Point(4,2));
	huruf[0].addPoint(Point(2,4));
	huruf[0].addPoint(Point(2,10));
	huruf[0].addPoint(Point(4,12));
	huruf[0].addPoint(Point(6,12));
	huruf[0].addPoint(Point(8,10));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(6,8));
	huruf[0].addPoint(Point(6,6));
	huruf[0].addPoint(Point(10,6));
	huruf[0].addPoint(Point(10,10));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,10));
	huruf[0].addPoint(Point(0,4));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf H
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(8,6));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf I
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(6,2));
	huruf[0].addPoint(Point(6,11));
	huruf[0].addPoint(Point(10,11));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(0,11));
	huruf[0].addPoint(Point(4,11));
	huruf[0].addPoint(Point(4,2));
	huruf[0].addPoint(Point(0,2));*/

	//Huruf J
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(0,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,12));
	huruf[0].addPoint(Point(8,12));
	huruf[0].addPoint(Point(8,2));
	huruf[0].addPoint(Point(0,2));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf K
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(6,7));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf L
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(2,10));
	huruf[0].addPoint(Point(10,10));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf M
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(5,6));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(8,6));
	huruf[0].addPoint(Point(5,8));
	huruf[0].addPoint(Point(2,6));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf N
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(8,12));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(2,4));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(1);
	huruf[0].setColor(200,200,200);*/

	//Huruf P
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,4));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(6,2));
	huruf[1].addPoint(Point(8,4));
	huruf[1].addPoint(Point(6,6));
	huruf[1].addPoint(Point(2,6));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);*/

	//Huruf R
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,4));
	huruf[0].addPoint(Point(8,8));
	huruf[0].addPoint(Point(4,8));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(2,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	huruf[1].addPoint(Point(2,2));
	huruf[1].addPoint(Point(6,2));
	huruf[1].addPoint(Point(8,4));
	huruf[1].addPoint(Point(6,6));
	huruf[1].addPoint(Point(2,6));
	huruf[1].setPriority(1);
	huruf[1].setColor(0,0,0);*/

	//Huruf T
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(6,2));
	huruf[0].addPoint(Point(6,14));
	huruf[0].addPoint(Point(4,14));
	huruf[0].addPoint(Point(4,2));
	huruf[0].addPoint(Point(0,2));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Huruf U
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(2,10));
	huruf[0].addPoint(Point(8,10));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Huruf V
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(5,12));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(6,14));
	huruf[0].addPoint(Point(4,14));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Huruf X
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(5,6));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(8,7));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(8,14));
	huruf[0].addPoint(Point(5,8));
	huruf[0].addPoint(Point(2,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(2,7));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Huruf Y
	/*huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(2,0));
	huruf[0].addPoint(Point(5,6));
	huruf[0].addPoint(Point(8,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(6,8));
	huruf[0].addPoint(Point(6,14));
	huruf[0].addPoint(Point(4,14));
	huruf[0].addPoint(Point(4,8));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);*/

	//Huruf Z
	huruf[0].addPoint(Point(0,0));
	huruf[0].addPoint(Point(10,0));
	huruf[0].addPoint(Point(10,2));
	huruf[0].addPoint(Point(2,12));
	huruf[0].addPoint(Point(10,12));
	huruf[0].addPoint(Point(10,14));
	huruf[0].addPoint(Point(0,14));
	huruf[0].addPoint(Point(0,12));
	huruf[0].addPoint(Point(8,2));
	huruf[0].addPoint(Point(0,2));
	huruf[0].setPriority(0);
	huruf[0].setColor(200,200,200);
	fb.anticlip(huruf, jumlah);

	//Huruf P
	
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