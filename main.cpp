#include "framebuffer.h"

using namespace std;

int main() {
	FrameBuffer fb;
	fb.clearScreen();
	fb.drawLine(Point(10, 10), Point(40, 40), Color(50, 150, 200));
	while(1) {}
	return 0;
}