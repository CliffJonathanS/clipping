#include "framebuffer.h"
#include <iostream>
#include <signal.h>
#include <string.h>
#include <vector>

#define NKETINGGIAN 14
#define NPULAU 17
#define NKOTA 34
#define PI acos(-1)

#define ZPULAU 0
#define ZKETINGGIAN 1
#define ZJALAN 2
#define ZPROVINSI 3
#define ZKOTA 4
#define ZTEXT 5


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
	//fb.clearScreen();

	Polygon pulau[NPULAU];
	Polygon marker[NKOTA];
	//Polygon ketinggian[NPULAU];
	vector<Polygon> kota;
	vector<Polygon> polygonFinal=fb.polygonparser();
	char c;
	int i;

	fb.drawRectangle(13,58,Color(200,0,0),10,kota);
	fb.drawRectangle(67,90,Color(200,0,0),10,kota);
	fb.drawRectangle(114,142,Color(200,0,0),10,kota);
	fb.drawRectangle(151,142,Color(200,0,0),10,kota);
	fb.drawRectangle(97,164,Color(200,0,0),10,kota);
	fb.drawRectangle(153,178,Color(200,0,0),10,kota);
	fb.drawRectangle(127,213,Color(200,0,0),10,kota);
	fb.drawRectangle(170,201,Color(200,0,0),10,kota);
	fb.drawRectangle(189,190,Color(200,0,0),10,kota);
	fb.drawRectangle(177,240,Color(200,0,0),10,kota);
	fb.drawRectangle(191,259,Color(200,0,0),10,kota);
	fb.drawRectangle(202,257,Color(100,0,100),20,kota);
	fb.drawRectangle(219,269,Color(200,0,0),10,kota);
	fb.drawRectangle(261,270,Color(200,0,0),10,kota);
	fb.drawRectangle(262,284,Color(200,0,0),10,kota);
	fb.drawRectangle(299,276,Color(200,0,0),10,kota);
	fb.drawRectangle(341,296,Color(200,0,0),10,kota);
	fb.drawRectangle(360,298,Color(200,0,0),10,kota);
	fb.drawRectangle(491,318,Color(200,0,0),10,kota);
	fb.drawRectangle(723,237,Color(200,0,0),10,kota);
	fb.drawRectangle(767,196,Color(200,0,0),10,kota);
	fb.drawRectangle(653,174,Color(200,0,0),10,kota);
	fb.drawRectangle(560,215,Color(200,0,0),10,kota);
	fb.drawRectangle(506,131,Color(200,0,0),10,kota);
	fb.drawRectangle(480,143,Color(200,0,0),10,kota);
	fb.drawRectangle(464,176,Color(200,0,0),10,kota);
	fb.drawRectangle(418,166,Color(200,0,0),10,kota);
	fb.drawRectangle(410,197,Color(200,0,0),10,kota);
	fb.drawRectangle(466,221,Color(200,0,0),10,kota);
	fb.drawRectangle(415,240,Color(200,0,0),10,kota);
	fb.drawRectangle(377,159,Color(200,0,0),10,kota);
	fb.drawRectangle(332,209,Color(200,0,0),10,kota);
	fb.drawRectangle(319,193,Color(200,0,0),10,kota);
	fb.drawRectangle(244,152,Color(200,0,0),10,kota);

	fb.anticlip(polygonFinal);
	fb.anticlip(kota);
	Point pusat = Point(500,500);
	float degree = -20.0 * PI/180.0;
	float anticlockwisedegree = 20.0 * PI/180.0;

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
			case 'Q' :
			case 'q' :
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(0,0,0));
					fb.fillPolygon(pulau[j], Color(0,0,0));
					for (i=0;i<pulau[j].getPoints().size();i++) {
						pulau[j].setPoint(i,Point(pulau[j].getPoints().at(i).rotate(degree,pusat)));
					}
				}
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(60,200,80));
					fb.fillPolygon(pulau[j], Color(60,200,80));
				}
				break;
			case 'W' :
			case 'w' :
				for (int j=0;j<NPULAU;j++) {
					fb.drawPolygon(pulau[j], Color(0,0,0));
					fb.fillPolygon(pulau[j], Color(0,0,0));
					for (i=0;i<pulau[j].getPoints().size();i++) {
						pulau[j].setPoint(i,Point(pulau[j].getPoints().at(i).rotate(anticlockwisedegree,pusat)));
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
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							//fb.drawPolygon(pulau[j], Color(0,0,0));
							//fb.fillPolygon(pulau[j], Color(0,0,0));
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX(), polygonFinal.at(j).getPoints().at(i).getY()-10));
							}

						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX(), kota.at(j).getPoints().at(i).getY()-10));
							}
						}
						//fb.clearScreen();
						/*for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(polygonFinal.at(j), Color(60,200,80));
							fb.fillPolygon(polygonFinal.at(j), Color(60,200,80));
						}*/
							fb.anticlip(polygonFinal);
							fb.anticlip(kota);
						break;
					case 'B':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							//fb.drawPolygon(polygonFinal.at(j), Color(0,0,0));
							//fb.fillPolygon(polygonFinal.at(j), Color(0,0,0));
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX(), polygonFinal.at(j).getPoints().at(i).getY()+10));
							}
						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX(), kota.at(j).getPoints().at(i).getY()+10));
							}
						}
						/*for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(polygonFinal.at(j), Color(60,200,80));
							fb.fillPolygon(polygonFinal.at(j), Color(60,200,80));
						}*/
							fb.anticlip(polygonFinal);
							fb.anticlip(kota);
						break;
					case 'C':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							//fb.drawPolygon(polygonFinal.at(j), Color(0,0,0));
							//fb.fillPolygon(polygonFinal.at(j), Color(0,0,0));
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX()+10, polygonFinal.at(j).getPoints().at(i).getY()));
							}
						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX()+10, kota.at(j).getPoints().at(i).getY()));
							}
						}
						/*
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(polygonFinal.at(j), Color(60,200,80));
							fb.fillPolygon(polygonFinal.at(j), Color(60,200,80));
						}*/
							fb.anticlip(polygonFinal);
							fb.anticlip(kota);
						break;
					case 'D':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							//fb.drawPolygon(polygonFinal.at(j), Color(0,0,0));
							//fb.fillPolygon(polygonFinal.at(j), Color(0,0,0));
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX()-10, polygonFinal.at(j).getPoints().at(i).getY()));
							}
						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX()-10, kota.at(j).getPoints().at(i).getY()));
							}
						}
						/*
						for (int j=0;j<NPULAU;j++) {
							fb.drawPolygon(polygonFinal.at(j), Color(60,200,80));
							fb.fillPolygon(polygonFinal.at(j), Color(60,200,80));
						}*/
						fb.anticlip(polygonFinal);
						fb.anticlip(kota);
						break;
				}
		}
	}
	return 0;
}