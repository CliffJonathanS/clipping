#include "framebuffer.h"
#include <iostream>
#include <signal.h>
#include <vector>


using namespace std;

int main(void) {
	FrameBuffer fb;
	//fb.clearScreen();
	vector<Polygon> vpol=fb.polygonparser();
	for(int i=0;i<vpol.size();i++){
		fb.drawPolygon(vpol.at(i),Color(200,200,200));
	}



	
	return 0;
}
