#include "framebuffer.h"
#include <iostream>
#include <signal.h>

using namespace std;

static volatile int run = 1;
static struct termios old, new1;

/* Initialize new1 terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new1 = old; /* make new1 settings same as old settings */
  new1.c_lflag &= ~ICANON; /* disable buffered i/o */
  new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new1); /* use these new1 terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

void INThandler(int sig) {
	run = 0;
}

int main(void) {
	FrameBuffer fb;
	fb.clearScreen();
	Polygon jawa;
	char c;
	int i;

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

	signal(SIGINT, INThandler);

	while (run) {
		c = getch();
		switch (c) {
			case 'Z' :
			case 'z' :
				fb.drawPolygon(jawa, Color(0,0,0));
				fb.fillPolygon(jawa, Color(0,0,0));
				for (i=0;i<jawa.getPoints().size();i++) {
					jawa.setPoint(i,Point((fb.getScreenWidth()/2)+1.25*(jawa.getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+1.25*(jawa.getPoints().at(i).getY()-fb.getScreenHeight()/2)));
				}
				fb.drawPolygon(jawa, Color(60,200,80));
				fb.fillPolygon(jawa, Color(60,200,80));
				break;
			case 'X' :
			case 'x' :
				fb.drawPolygon(jawa, Color(0,0,0));
				fb.fillPolygon(jawa, Color(0,0,0));
				for (i=0;i<jawa.getPoints().size();i++) {
					jawa.setPoint(i,Point((fb.getScreenWidth()/2)+0.8*(jawa.getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+0.8*(jawa.getPoints().at(i).getY()-fb.getScreenHeight()/2)));
				}
				fb.drawPolygon(jawa, Color(60,200,80));
				fb.fillPolygon(jawa, Color(60,200,80));
				break;
		}
	}
	return 0;
}