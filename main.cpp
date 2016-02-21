#include "framebuffer.h"
#include <iostream>
#include <signal.h>

#define NPULAU 2

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
	Polygon pulau[NPULAU];
	char c;
	int i;

	pulau[0].addPoint(Point(257,258));
	pulau[0].addPoint(Point(280,270));
	pulau[0].addPoint(Point(287,277));
	pulau[0].addPoint(Point(287,281));
	pulau[0].addPoint(Point(315,307));
	pulau[0].addPoint(Point(320,307));
	pulau[0].addPoint(Point(355,337));
	pulau[0].addPoint(Point(380,365));
	pulau[0].addPoint(Point(388,397));
	pulau[0].addPoint(Point(360,397));
	pulau[0].addPoint(Point(310,360));
	pulau[0].addPoint(Point(250,260));


	pulau[1].addPoint(Point(400,410));
	pulau[1].addPoint(Point(440,415));
	pulau[1].addPoint(Point(450,420));
	pulau[1].addPoint(Point(480,420));
	pulau[1].addPoint(Point(485,413));
	pulau[1].addPoint(Point(525,415));
	pulau[1].addPoint(Point(532,425));
	pulau[1].addPoint(Point(565,425));
	pulau[1].addPoint(Point(565,450));
	pulau[1].addPoint(Point(532,445));
	pulau[1].addPoint(Point(485,447));
	pulau[1].addPoint(Point(470,440));
	pulau[1].addPoint(Point(445,440));
	pulau[1].addPoint(Point(443,445));
	pulau[1].addPoint(Point(405,435));
	pulau[1].addPoint(Point(408,427));
	pulau[1].addPoint(Point(395,425));

	
	for (int j=0;j<NPULAU;j++) {
		fb.drawPolygon(pulau[j], Color(60,200,80));
		fb.fillPolygon(pulau[j], Color(60,200,80));
	}

	signal(SIGINT, INThandler);

	while (run) {
		c = getch();
		switch (c) {
			case 'Z' :
			case 'z' :
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(0,0,0));
					fb.fillPolygon(pulau[j], Color(0,0,0));
					for (i=0;i<pulau[j].getPoints().size();i++) {
						pulau[j].setPoint(i,Point((fb.getScreenWidth()/2)+1.25*(pulau[j].getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+1.25*(pulau[j].getPoints().at(i).getY()-fb.getScreenHeight()/2)));
					}
					
				}
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(60,200,80));
					fb.fillPolygon(pulau[j], Color(60,200,80));
				}
				break;
			case 'X' :
			case 'x' :
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(0,0,0));
					fb.fillPolygon(pulau[j], Color(0,0,0));
					for (i=0;i<pulau[j].getPoints().size();i++) {
						pulau[j].setPoint(i,Point((fb.getScreenWidth()/2)+0.8*(pulau[j].getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+0.8*(pulau[j].getPoints().at(i).getY()-fb.getScreenHeight()/2)));
					}
				}
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(60,200,80));
					fb.fillPolygon(pulau[j], Color(60,200,80));
				}
				break;
			case '\033':
				getch();
				switch(getch()) {
					case 'A':
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(0,0,0));
							fb.fillPolygon(pulau[j], Color(0,0,0));
							for (i=0;i<pulau[j].getPoints().size();i++) {
								pulau[j].setPoint(i,Point(pulau[j].getPoints().at(i).getX(), pulau[j].getPoints().at(i).getY()+10));
							}
						}
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(60,200,80));
							fb.fillPolygon(pulau[j], Color(60,200,80));
						}
						break;
					case 'B':
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(0,0,0));
							fb.fillPolygon(pulau[j], Color(0,0,0));
							for (i=0;i<pulau[j].getPoints().size();i++) {
								pulau[j].setPoint(i,Point(pulau[j].getPoints().at(i).getX(), pulau[j].getPoints().at(i).getY()-10));
							}
						}
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(60,200,80));
							fb.fillPolygon(pulau[j], Color(60,200,80));
						}
						break;
					case 'C':
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(0,0,0));
							fb.fillPolygon(pulau[j], Color(0,0,0));
							for (i=0;i<pulau[j].getPoints().size();i++) {
								pulau[j].setPoint(i,Point(pulau[j].getPoints().at(i).getX()-10, pulau[j].getPoints().at(i).getY()));
							}
						}
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(60,200,80));
							fb.fillPolygon(pulau[j], Color(60,200,80));
						}
						break;
					case 'D':
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(0,0,0));
							fb.fillPolygon(pulau[j], Color(0,0,0));
							for (i=0;i<pulau[j].getPoints().size();i++) {
								pulau[j].setPoint(i,Point(pulau[j].getPoints().at(i).getX()+10, pulau[j].getPoints().at(i).getY()));
							}
						}
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(pulau[j], Color(60,200,80));
							fb.fillPolygon(pulau[j], Color(60,200,80));
						}
						break;
				}
		}
	}
	return 0;
}