#include "framebuffer.h"
#include <iostream>

#define PI 3.14159
int main(){
	Point a = Point(10,10);
	float degree = 270.0 * PI/180.0;
	
	Point pusat = Point(0,0);
	a.rotate(degree, pusat);
	printf("%f,%f\n",a.getX(), a.getY() );
}