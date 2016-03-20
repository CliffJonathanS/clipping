#include "framebuffer.h"
#include <iostream>
#include <signal.h>
#include <string.h>
#include <vector>
#include <algorithm>

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
	vector<char> toogleMenu;
	bool menuKetinggian = false, menuJalan = false, menuProvinsi = false, menuKota = false, menuText = false;
	//Polygon ketinggian[NPULAU];
	vector<Polygon> kota;
	vector<Polygon> polygonFinal=fb.polygonparser();

	fb.addpolygonsfinal("BANDA ACEH",Point(7,48), polygonFinal);
	fb.addpolygonsfinal("MEDAN",Point(65,80), polygonFinal);
	fb.addpolygonsfinal("PADANG",Point(34,164), polygonFinal);
	fb.addpolygonsfinal("PEKAN BARU",Point(45,132), polygonFinal);
	fb.addpolygonsfinal("TANJUNG PINANG",Point(124,122), polygonFinal);
	fb.addpolygonsfinal("JAMBI",Point(142,168), polygonFinal);
	fb.addpolygonsfinal("BENGKULU",Point(74,198), polygonFinal);
	fb.addpolygonsfinal("PANGKAL PINANG",Point(175,180), polygonFinal);
	fb.addpolygonsfinal("BANDAR LAMPUNG",Point(121,225), polygonFinal);
	fb.addpolygonsfinal("PALEMBANG",Point(171,191), polygonFinal);
	fb.addpolygonsfinal("JAKARTA",Point(198,249), polygonFinal);
	fb.addpolygonsfinal("BANDUNG",Point(205,283), polygonFinal);
	fb.addpolygonsfinal("SEMARANG",Point(248,259), polygonFinal);
	fb.addpolygonsfinal("SURABAYA",Point(298,268), polygonFinal);
	fb.addpolygonsfinal("SERANG",Point(123,264), polygonFinal);
	fb.addpolygonsfinal("DENPASAR",Point(334,278), polygonFinal);
	fb.addpolygonsfinal("MATARAM",Point(335,308), polygonFinal);
	fb.addpolygonsfinal("KUPANG",Point(472,300), polygonFinal);
	fb.addpolygonsfinal("PONTIANAK",Point(207,138), polygonFinal);
	fb.addpolygonsfinal("PALANGKARAYA",Point(278,171), polygonFinal);
	fb.addpolygonsfinal("BANJARMASIN",Point(324,202), polygonFinal);
	fb.addpolygonsfinal("SAMARINDA",Point(361,141), polygonFinal);
	fb.addpolygonsfinal("MANADO",Point(495,113), polygonFinal);
	fb.addpolygonsfinal("PALU",Point(400,150), polygonFinal);
	fb.addpolygonsfinal("MAKASSAR",Point(379,223), polygonFinal);
	fb.addpolygonsfinal("KENDARI",Point(454,213), polygonFinal);
	fb.addpolygonsfinal("GORONTALO",Point(458,136), polygonFinal);
	fb.addpolygonsfinal("MAMUJU",Point(385,184), polygonFinal);
	fb.addpolygonsfinal("AMBON",Point(548,201), polygonFinal);
	fb.addpolygonsfinal("TERNATE",Point(551,118), polygonFinal);
	fb.addpolygonsfinal("MANOKWARI",Point(628,156), polygonFinal);
	fb.addpolygonsfinal("JAYAPURA",Point(706,220), polygonFinal);	

	/*fb.addpolygonsfinal("5,201,002 JIWA",Point(7,28), polygonFinal);
	fb.addpolygonsfinal("12,450,911 JIWA",Point(65,60), polygonFinal);
	fb.addpolygonsfinal("4,566,126 JIWA",Point(57,146), polygonFinal);
	fb.addpolygonsfinal("4,579,219 JIWA",Point(105,112), polygonFinal);
	fb.addpolygonsfinal("1,274,848 JIWA",Point(134,134), polygonFinal);
	fb.addpolygonsfinal("2,635,968 JIWA",Point(147,147), polygonFinal);
	fb.addpolygonsfinal("1,549,273 JIWA",Point(74,195), polygonFinal);
	fb.addpolygonsfinal("1,043,456 JIWA",Point(185,160), polygonFinal);
	fb.addpolygonsfinal("7,116,177 JIWA",Point(121,225), polygonFinal);
	fb.addpolygonsfinal("6,782,339 JIWA",Point(176,191), polygonFinal);
	fb.addpolygonsfinal("8,860,381 JIWA",Point(198,228), polygonFinal);
	fb.addpolygonsfinal("38,965,440 JIWA",Point(210,262), polygonFinal);
	fb.addpolygonsfinal("31,977,968 JIWA",Point(248,237), polygonFinal);
	fb.addpolygonsfinal("36,294,280 JIWA",Point(298,245), polygonFinal);
	fb.addpolygonsfinal("9,028,816 JIWA",Point(150,244), polygonFinal);
	fb.addpolygonsfinal("3,383,572 JIWA",Point(334,264), polygonFinal);
	fb.addpolygonsfinal("4,184,411 JIWA",Point(335,293), polygonFinal);
	fb.addpolygonsfinal("4,260,294 JIWA",Point(472,290), polygonFinal);
	fb.addpolygonsfinal("4,052,345 JIWA",Point(207,138), polygonFinal);
	fb.addpolygonsfinal("1,914,900 JIWA",Point(278,176), polygonFinal);
	fb.addpolygonsfinal("3,446,631 JIWA",Point(324,202), polygonFinal);
	fb.addpolygonsfinal("2,848,798 JIWA",Point(361,131), polygonFinal);
	fb.addpolygonsfinal("2,128,780 JIWA",Point(495,103), polygonFinal);
	fb.addpolygonsfinal("2,294,841 JIWA",Point(402,139), polygonFinal);
	fb.addpolygonsfinal("7,509,704 JIWA",Point(379,223), polygonFinal);
	fb.addpolygonsfinal("1,963,025 JIWA",Point(400,140), polygonFinal);
	fb.addpolygonsfinal("922,176 JIWA",Point(458,136), polygonFinal);
	fb.addpolygonsfinal("969,429 JIWA",Point(385,169), polygonFinal);
	fb.addpolygonsfinal("1,251,539 JIWA",Point(548,191), polygonFinal);
	fb.addpolygonsfinal("884,142 JIWA",Point(541,118), polygonFinal);
	fb.addpolygonsfinal("643,012 JIWA",Point(628,146), polygonFinal);
	fb.addpolygonsfinal("1,875,388 JIWA",Point(706,235), polygonFinal);	*/
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

	fb.addpolygonsfinal("SAY A", Point(100,100), polygonFinal);


	polygonFinal.insert( polygonFinal.end(), kota.begin(), kota.end() );
	toogleMenu.push_back(ZPULAU);


	fb.anticlip(polygonFinal,toogleMenu);
	Point pusat = Point(500,500);
	float degree = -20.0 * PI/180.0;
	float anticlockwisedegree = 20.0 * PI/180.0;

	signal(SIGINT, INThandler);

	while (run) {
		
		c = getch();
		switch (c) {
			//Toogle On ketinggian
			case '1':
				if (menuKetinggian){
					toogleMenu.erase(remove(toogleMenu.begin(), toogleMenu.end(), (char)ZKETINGGIAN), toogleMenu.end());
					menuKetinggian = !menuKetinggian;
				} else {
					toogleMenu.push_back(ZKETINGGIAN);
					menuKetinggian = !menuKetinggian;
				}
				fb.clearScreen();
				fb.anticlip(polygonFinal,toogleMenu);
				break;
			//Toogle On jalan
			case '2':
				if (menuJalan){
					toogleMenu.erase(remove(toogleMenu.begin(), toogleMenu.end(), ZJALAN), toogleMenu.end());
					menuJalan = !menuJalan;
				} else {
					toogleMenu.push_back(ZJALAN);
					menuJalan = !menuJalan;
				}
				
				fb.clearScreen();
				fb.anticlip(polygonFinal,toogleMenu);
				break;
			//Toogle On batas provinsi
			case '3':
				if (menuProvinsi){
					toogleMenu.erase(remove(toogleMenu.begin(), toogleMenu.end(), ZPROVINSI), toogleMenu.end());
					menuProvinsi = !menuProvinsi;
				} else {
					toogleMenu.push_back(ZPROVINSI);
					menuProvinsi = !menuProvinsi;
				}
				
				fb.clearScreen();
				fb.anticlip(polygonFinal,toogleMenu);
				break;
			//Toogle On kota
			case '4':
				if (menuKota){
					toogleMenu.erase(remove(toogleMenu.begin(), toogleMenu.end(), ZKOTA), toogleMenu.end());
					menuKota = !menuKota;
				} else {
					toogleMenu.push_back(ZKOTA);
					menuKota = !menuKota;
				}
				fb.clearScreen();
				
				fb.anticlip(polygonFinal,toogleMenu);
				break;
			//Toogle On teks
			case '5':
				if (menuText){
					toogleMenu.erase(remove(toogleMenu.begin(), toogleMenu.end(), ZTEXT), toogleMenu.end());
					toogleMenu.erase(remove(toogleMenu.begin(), toogleMenu.end(), ZTEXT+1), toogleMenu.end());
					menuText = !menuText;
				} else {
					toogleMenu.push_back(ZTEXT);
					toogleMenu.push_back(ZTEXT+1);
					menuText = !menuText;
				}
				fb.clearScreen();
				fb.anticlip(polygonFinal,toogleMenu);
				break;
			//Zoom In
			case 'Z' :
			case 'z' :
			fb.clearScreen();
				for (int j=0;j<polygonFinal.size();j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point((fb.getScreenWidth()/2)+1.25*(polygonFinal.at(j).getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+1.25*(polygonFinal.at(j).getPoints().at(i).getY()-fb.getScreenHeight()/2)));
					}
					
				}
				fb.anticlip(polygonFinal,toogleMenu);
				
				break;
			//Zoom Out
			case 'X' :
			case 'x' :
				fb.clearScreen();
				for (int j=0;j<polygonFinal.size();j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point((fb.getScreenWidth()/2)+0.8*(polygonFinal.at(j).getPoints().at(i).getX()-fb.getScreenWidth()/2), (fb.getScreenHeight()/2)+0.8*(polygonFinal.at(j).getPoints().at(i).getY()-fb.getScreenHeight()/2)));
					}
				}

				fb.anticlip(polygonFinal,toogleMenu);
				
				break;
			//Rotate degree
			case 'Q' :
			case 'q' :
				fb.clearScreen();
				for (int j=0;j<polygonFinal.size();j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).rotate(degree,pusat)));
					}
				}
				fb.anticlip(polygonFinal,toogleMenu);
				break;

			//Rotate anti clockwise degree
			case 'W' :
			case 'w' :
				fb.clearScreen();
				for (int j=0;j<polygonFinal.size();j++) {
					for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
						polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).rotate(anticlockwisedegree,pusat)));
					}
				}
				fb.anticlip(polygonFinal,toogleMenu);
				break;
			//Move with arrow key
			case '\033':
				getch();
				switch(getch()) {
					//move arrow up
					case 'A':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX(), polygonFinal.at(j).getPoints().at(i).getY()-10));
							}

						}
						fb.anticlip(polygonFinal,toogleMenu);
						break;
					//move arrow down
					case 'B':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX(), polygonFinal.at(j).getPoints().at(i).getY()+10));
							}
						}
						fb.anticlip(polygonFinal,toogleMenu);
						break;
					//move arrow right
					case 'C':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX()+10, polygonFinal.at(j).getPoints().at(i).getY()));
							}
						}
						fb.anticlip(polygonFinal,toogleMenu);
						
						break;
					//move arrow left
					case 'D':
						fb.clearScreen();
						for (int j=0;j<polygonFinal.size();j++) {
							
							for (i=0;i<polygonFinal.at(j).getPoints().size();i++) {
								polygonFinal.at(j).setPoint(i,Point(polygonFinal.at(j).getPoints().at(i).getX()-10, polygonFinal.at(j).getPoints().at(i).getY()));
							}
						}
						fb.anticlip(polygonFinal,toogleMenu);
						break;
				}
		}
	}
	return 0;
}