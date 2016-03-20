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
	fb.clearScreen();

	Polygon pulau[NPULAU];
	Polygon marker[NKOTA];
	//Polygon ketinggian[NPULAU];
	vector<Polygon> kota;
	vector<Polygon> bat;
	vector<Polygon> polygonFinal=fb.polygonparser();

	fb.addpolygonsfinal("SAYA",Point(100,100), polygonFinal);
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


	Polygon batas[10];

	/*-------- Sumatra --------*/
	batas[0].addPoint(Point(19,78));
	batas[0].addPoint(Point(24,78));
	batas[0].addPoint(Point(32,75));
	batas[0].addPoint(Point(52,76));
	batas[0].addPoint(Point(65,89));
	batas[0].addPoint(Point(66,94));
	batas[0].addPoint(Point(94,116));
	batas[0].addPoint(Point(109,129));
	batas[0].addPoint(Point(107,126));
	batas[0].addPoint(Point(112,129));
	batas[0].addPoint(Point(122,139));
	batas[0].addPoint(Point(131,147));
	batas[0].addPoint(Point(140,155));
	batas[0].addPoint(Point(144,159));
	batas[0].addPoint(Point(149,168));
	batas[0].addPoint(Point(157,172));
	batas[0].addPoint(Point(153,178));
	batas[0].addPoint(Point(152,184));
	batas[0].addPoint(Point(159,189));
	batas[0].addPoint(Point(167,190));
	batas[0].addPoint(Point(170,202));
	batas[0].addPoint(Point(174,205));
	batas[0].addPoint(Point(175,212));
	batas[0].addPoint(Point(185,211));
	batas[0].addPoint(Point(186,219));
	batas[0].addPoint(Point(187,226));
	batas[0].addPoint(Point(187,224));
	batas[0].addPoint(Point(186,217));
	batas[0].addPoint(Point(185,209));
	batas[0].addPoint(Point(175,210));	
	batas[0].addPoint(Point(174,203));
	batas[0].addPoint(Point(170,200));
	batas[0].addPoint(Point(167,188));
	batas[0].addPoint(Point(159,187));
	batas[0].addPoint(Point(152,182));
	batas[0].addPoint(Point(153,176));
	batas[0].addPoint(Point(157,163));
	batas[0].addPoint(Point(149,166));
	batas[0].addPoint(Point(144,167));
	batas[0].addPoint(Point(140,153));
	batas[0].addPoint(Point(131,145));
	batas[0].addPoint(Point(122,137));
	batas[0].addPoint(Point(112,127));
	batas[0].addPoint(Point(107,114));
	batas[0].addPoint(Point(109,127));
	batas[0].addPoint(Point(94,114));
	batas[0].addPoint(Point(66,92));
	batas[0].addPoint(Point(65,87));
	batas[0].addPoint(Point(52,74));
	batas[0].addPoint(Point(32,73));
	batas[0].addPoint(Point(24,76));
	batas[0].addPoint(Point(19,78));

	batas[1].addPoint(Point(19,76));
	batas[1].addPoint(Point(50,98));
	batas[1].addPoint(Point(50,100));
	batas[1].addPoint(Point(60,110));
	batas[1].addPoint(Point(90,152));
	batas[1].addPoint(Point(115,197));
	batas[1].addPoint(Point(150,219));
	batas[1].addPoint(Point(150,217));
	batas[1].addPoint(Point(115,195));
	batas[1].addPoint(Point(90,150));
	batas[1].addPoint(Point(62,110));
	batas[1].addPoint(Point(52,100));
	batas[1].addPoint(Point(52,96));
	batas[1].addPoint(Point(19,76));

	batas[2].addPoint(Point(90,152));	
	batas[2].addPoint(Point(135,165));
	batas[2].addPoint(Point(150,180));
	batas[2].addPoint(Point(115,197));
	batas[2].addPoint(Point(130,212));
	batas[2].addPoint(Point(175,225));
	batas[2].addPoint(Point(173,225));
	batas[2].addPoint(Point(128,210));
	batas[2].addPoint(Point(117,195));
	batas[2].addPoint(Point(152,182));
	batas[2].addPoint(Point(137,163));
	batas[2].addPoint(Point(90,152));
	
	/*-------- Sumatra --------*/

	/*-------- Jawa --------*/
	batas[3].addPoint(Point(190,260));	
	batas[3].addPoint(Point(230,280));
	batas[3].addPoint(Point(280,270));
	batas[3].addPoint(Point(300,290));
	batas[3].addPoint(Point(330,270));
	batas[3].addPoint(Point(330,268));
	batas[3].addPoint(Point(300,288));
	batas[3].addPoint(Point(280,268));
	batas[3].addPoint(Point(230,278));
	batas[3].addPoint(Point(190,260));	

	batas[4].addPoint(Point(190,260));	
	batas[4].addPoint(Point(230,270));
	batas[4].addPoint(Point(280,290));
	batas[4].addPoint(Point(300,280));
	batas[4].addPoint(Point(330,290));
	batas[4].addPoint(Point(330,288));
	batas[4].addPoint(Point(300,278));
	batas[4].addPoint(Point(280,288));
	batas[4].addPoint(Point(230,268));
	batas[4].addPoint(Point(190,260));	

	/*-------- Jawa --------*/

	for (i=0; i<5; i++){
		batas[i].setPriority(0);
		batas[i].setColor(Color(255,131,250));
		bat.push_back(batas[i]);
		fb.anticlip(bat);
	}
	while (run) {
		
		c = getch();
		switch (c) {
			case 'Z' :
			case 'z' :
			fb.clearScreen();
				for (int j=0;j<NPULAU;j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point((fb.getScreenWidth()/2)+1.25*(polygonFinal.at(j).getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+1.25*(polygonFinal.at(j).getPoints().at(i).getY()-fb.getScreenHeight()/2)));
					}
					
				}
				fb.anticlip(polygonFinal);
				fb.anticlip(kota);
				break;
			case 'X' :
			case 'x' :
				fb.clearScreen();
				for (int j=0;j<NPULAU;j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point((fb.getScreenWidth()/2)+0.8*(polygonFinal.at(j).getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+0.8*(polygonFinal.at(j).getPoints().at(i).getY()-fb.getScreenHeight()/2)));
					}
				}

				fb.anticlip(polygonFinal);
				fb.anticlip(kota);
				break;
			case 'Q' :
			case 'q' :
				fb.clearScreen();
				for (int j=0;j<NPULAU;j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).rotate(degree,pusat)));
					}
				}
				fb.anticlip(polygonFinal);
				fb.anticlip(kota);

				break;
			case 'W' :
			case 'w' :

				fb.clearScreen();
				for (int j=0;j<NPULAU;j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).rotate(anticlockwisedegree,pusat)));
					}
				}
				fb.anticlip(polygonFinal);
				fb.anticlip(kota);
				break;
			case '\033':
				getch();
				switch(getch()) {
					case 'A':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX(), polygonFinal.at(j).getPoints().at(i).getY()-10));
							}

						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX(), kota.at(j).getPoints().at(i).getY()-10));
							}
						}
						fb.anticlip(polygonFinal);
						fb.anticlip(kota);
						break;
					case 'B':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX(), polygonFinal.at(j).getPoints().at(i).getY()+10));
							}
						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX(), kota.at(j).getPoints().at(i).getY()+10));
							}
						}
						fb.anticlip(polygonFinal);
						fb.anticlip(kota);
						break;
					case 'C':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX()+10, polygonFinal.at(j).getPoints().at(i).getY()));
							}
						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX()+10, kota.at(j).getPoints().at(i).getY()));
							}
						}
						fb.anticlip(polygonFinal);
						fb.anticlip(kota);
						break;
					case 'D':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX()-10, polygonFinal.at(j).getPoints().at(i).getY()));
							}
						}
						for (int j=0;j<NKOTA;j++) {
							for (i=0;i<kota.at(j).getPoints().size();i++) {
								kota.at(j).setPoint(i,Point(kota.at(j).getPoints().at(i).getX()-10, kota.at(j).getPoints().at(i).getY()));
							}
						}
						fb.anticlip(polygonFinal);
						fb.anticlip(kota);
						break;
				}
		}
	}
	return 0;
}
