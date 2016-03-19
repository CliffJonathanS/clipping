#include "framebuffer.h"
#include <iostream>
#include <string.h>

int main(void) {
	FrameBuffer fb;
	fb.clearScreen();
	fb.CohenSutherlandLineClipAndDraw(Point(50,50),Point(500,500),Color(200,200,200)) ;

	fb.CohenSutherlandLineClipAndDraw(Point(50,50),Point(500,400),Color(200,200,200)) ;

	fb.CohenSutherlandLineClipAndDraw(Point(50,50),Point(500,300),Color(200,200,200)) ;

	fb.CohenSutherlandLineClipAndDraw(Point(50,50),Point(500,200),Color(200,200,200)) ;

	fb.CohenSutherlandLineClipAndDraw(Point(50,50),Point(500,100),Color(200,200,200)) ;
	

}