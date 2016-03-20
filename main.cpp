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

#define LEFTWINDOW 0
#define RIGHTWINDOW 700
#define UPWINDOW 0
#define DOWNWINDOW 700


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
	vector<Polygon> bat;
	vector<Polygon> polygonFinal=fb.polygonparser();

	//Nama kota
	fb.addpolygonsfinal("BANDA ACEH",Point(7,33), polygonFinal,0.7);
	fb.addpolygonsfinal("MEDAN",Point(65,80), polygonFinal,0.7);
	fb.addpolygonsfinal("PADANG",Point(34,164), polygonFinal,0.7);
	fb.addpolygonsfinal("PEKAN BARU",Point(40,132), polygonFinal,0.7);
	fb.addpolygonsfinal("TANJUNG PINANG",Point(124,117), polygonFinal,0.7);
	fb.addpolygonsfinal("JAMBI",Point(142,158), polygonFinal,0.7);
	fb.addpolygonsfinal("BENGKULU",Point(74,198), polygonFinal,0.7);
	fb.addpolygonsfinal("PANGKAL PINANG",Point(165,175), polygonFinal,0.7);
	fb.addpolygonsfinal("BANDAR LAMPUNG",Point(121,225), polygonFinal,0.7);
	fb.addpolygonsfinal("PALEMBANG",Point(171,193), polygonFinal,0.7);
	fb.addpolygonsfinal("JAKARTA",Point(188,251), polygonFinal,0.7);
	fb.addpolygonsfinal("BANDUNG",Point(205,283), polygonFinal,0.7);
	fb.addpolygonsfinal("SEMARANG",Point(258,249), polygonFinal,0.7);
	fb.addpolygonsfinal("YOGJAKARTA",Point(243,300), polygonFinal,0.7);
	fb.addpolygonsfinal("SURABAYA",Point(288,268), polygonFinal,0.7);
	fb.addpolygonsfinal("SERANG",Point(123,264), polygonFinal,0.7);
	fb.addpolygonsfinal("DENPASAR",Point(334,283), polygonFinal,0.7);
	fb.addpolygonsfinal("MATARAM",Point(335,318), polygonFinal,0.7);
	fb.addpolygonsfinal("KUPANG",Point(472,300), polygonFinal,0.7);
	fb.addpolygonsfinal("PONTIANAK",Point(207,138), polygonFinal,0.7);
	fb.addpolygonsfinal("PALANGKARAYA",Point(278,166), polygonFinal,0.7);
	fb.addpolygonsfinal("BANJARMASIN",Point(324,202), polygonFinal,0.7);
	fb.addpolygonsfinal("SAMARINDA",Point(356,136), polygonFinal,0.7);
	fb.addpolygonsfinal("MANADO",Point(495,113), polygonFinal,0.7);
	fb.addpolygonsfinal("PALU",Point(400,150), polygonFinal,0.7);
	fb.addpolygonsfinal("MAKASSAR",Point(379,223), polygonFinal,0.7);
	fb.addpolygonsfinal("KENDARI",Point(454,213), polygonFinal,0.7);
	fb.addpolygonsfinal("GORONTALO",Point(458,136), polygonFinal,0.7);
	fb.addpolygonsfinal("MAMUJU",Point(385,184), polygonFinal,0.7);
	fb.addpolygonsfinal("AMBON",Point(548,201), polygonFinal,0.7);
	fb.addpolygonsfinal("TERNATE",Point(551,118), polygonFinal,0.7);
	fb.addpolygonsfinal("MANOKWARI",Point(628,156), polygonFinal,0.7);
	fb.addpolygonsfinal("JAYAPURA",Point(706,220), polygonFinal,0.7);	

	//Populasi
	fb.addpolygonsfinal("5,2 JUTA JIWA",Point(0,43), polygonFinal,0.5);
	fb.addpolygonsfinal("12,4 JUTA JIWA",Point(55,90), polygonFinal,0.5);
	fb.addpolygonsfinal("4,5 JUTA JIWA",Point(24,174), polygonFinal,0.5);
	fb.addpolygonsfinal("4,5 JUTA JIWA",Point(45,142), polygonFinal,0.5);
	fb.addpolygonsfinal("1,274,848 JIWA",Point(124,127), polygonFinal,0.5);
	fb.addpolygonsfinal("2,635,968 JIWA",Point(142,168), polygonFinal,0.5);
	fb.addpolygonsfinal("1,549,273 JIWA",Point(74,208), polygonFinal,0.5);
	fb.addpolygonsfinal("1,043,456 JIWA",Point(175,184), polygonFinal,0.5);
	fb.addpolygonsfinal("7,116,177 JIWA",Point(121,235), polygonFinal,0.5);	
	fb.addpolygonsfinal("6,782,339 JIWA",Point(171,201), polygonFinal,0.5);
	fb.addpolygonsfinal("8,860,381 JIWA",Point(173,261), polygonFinal,0.5);
	fb.addpolygonsfinal("38,965,440 JIWA",Point(175,293), polygonFinal,0.5);
	fb.addpolygonsfinal("31,977,968 JIWA",Point(258,259), polygonFinal,0.5);
	fb.addpolygonsfinal("3,594,854 JIWA",Point(243,310), polygonFinal,0.5);
	fb.addpolygonsfinal("36,294,280 JIWA",Point(288,278), polygonFinal,0.5);
	fb.addpolygonsfinal("9,028,816 JIWA",Point(123,274), polygonFinal,0.5);
	fb.addpolygonsfinal("3,383,572 JIWA",Point(334,293), polygonFinal,0.5);
	fb.addpolygonsfinal("4,184,411 JIWA",Point(335,328), polygonFinal,0.5);
	fb.addpolygonsfinal("4,260,294 JIWA",Point(472,310), polygonFinal,0.5);
	fb.addpolygonsfinal("4,052,345 JIWA",Point(207,148), polygonFinal,0.5);
	fb.addpolygonsfinal("1,914,900 JIWA",Point(278,176), polygonFinal,0.5);
	fb.addpolygonsfinal("3,446,631 JIWA",Point(324,212), polygonFinal,0.5);
	fb.addpolygonsfinal("2,848,798 JIWA",Point(356,146), polygonFinal,0.5);
	fb.addpolygonsfinal("2,128,780 JIWA",Point(495,123), polygonFinal,0.5);
	fb.addpolygonsfinal("2,294,841 JIWA",Point(400,160), polygonFinal,0.5);
	fb.addpolygonsfinal("7,509,704 JIWA",Point(379,233), polygonFinal,0.5);
	fb.addpolygonsfinal("1,963,025 JIWA",Point(454,223), polygonFinal,0.5);
	fb.addpolygonsfinal("922,176 JIWA",Point(458,146), polygonFinal,0.5);
	fb.addpolygonsfinal("969,429 JIWA",Point(385,194), polygonFinal,0.5);
	fb.addpolygonsfinal("1,251,539 JIWA",Point(548,211), polygonFinal,0.5);
	fb.addpolygonsfinal("884,142 JIWA",Point(551,128), polygonFinal,0.5);
	fb.addpolygonsfinal("643,012 JIWA",Point(628,166), polygonFinal,0.5);
	fb.addpolygonsfinal("1,875,388 JIWA",Point(706,230), polygonFinal,0.5);
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
	batas[3].addPoint(Point(330,300));
	batas[3].addPoint(Point(330,298));
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

	/*-------- Kalimantan --------*/
	batas[5].addPoint(Point(230,140));
	batas[5].addPoint(Point(280,190));
	batas[5].addPoint(Point(310,162));
	batas[5].addPoint(Point(340,210));
	batas[5].addPoint(Point(380,110));
	batas[5].addPoint(Point(380,108));
	batas[5].addPoint(Point(340,208));
	batas[5].addPoint(Point(310,160));
	batas[5].addPoint(Point(280,188));
	batas[5].addPoint(Point(230,140));

	batas[6].addPoint(Point(310,150));
	batas[6].addPoint(Point(380,145));
	batas[6].addPoint(Point(360,90));
	batas[6].addPoint(Point(380,80));
	batas[6].addPoint(Point(380,78));
	batas[6].addPoint(Point(360,88));
	batas[6].addPoint(Point(380,143));
	batas[6].addPoint(Point(310,148));
	/*-------- Kalimantan --------*/

	/*-------- Sulawesi --------*/
	batas[7].addPoint(Point(520,145));
	batas[7].addPoint(Point(425,150));
	batas[7].addPoint(Point(420,250));
	batas[7].addPoint(Point(430,250));
	batas[7].addPoint(Point(435,200));
	batas[7].addPoint(Point(445,190));
	batas[7].addPoint(Point(445,188));
	batas[7].addPoint(Point(434,198));
	batas[7].addPoint(Point(428,248));
	batas[7].addPoint(Point(422,248));
	batas[7].addPoint(Point(427,152));
	batas[7].addPoint(Point(520,145));

	batas[8].addPoint(Point(445,200));
	batas[8].addPoint(Point(455,240));
	batas[8].addPoint(Point(460,230));
	batas[8].addPoint(Point(455,195));
	batas[8].addPoint(Point(453,195));
	batas[8].addPoint(Point(458,228));
	batas[8].addPoint(Point(455,238));
	batas[8].addPoint(Point(445,200));
	/*-------- Sulawesi --------*/

	/*-------- Papua --------*/
	batas[9].addPoint(Point(770,238));
	batas[9].addPoint(Point(700,225));
	batas[9].addPoint(Point(700,223));
	batas[9].addPoint(Point(770,236));
	batas[9].addPoint(Point(770,238));
	/*-------- Papua --------*/


	for (i=0; i<5; i++){
		batas[i].setPriority(ZPROVINSI);
		batas[i].setColor(Color(255,131,250));
		bat.push_back(batas[i]);
		//fb.anticlip(bat);
	}

	polygonFinal.insert( polygonFinal.end(), kota.begin(), kota.end() );
	polygonFinal.insert( polygonFinal.end(), bat.begin(), bat.end() );
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