#include "framebuffer.h"
#include <iostream>
#include <signal.h>

#define NPULAU 17

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
	char c;
	int i;

	pulau[0].addPoint(Point(17,60));
	pulau[0].addPoint(Point(24,60));
	pulau[0].addPoint(Point(32,65));
	pulau[0].addPoint(Point(52,66));
	pulau[0].addPoint(Point(65,79));
	pulau[0].addPoint(Point(66,84));
	pulau[0].addPoint(Point(94,106));
	pulau[0].addPoint(Point(109,119));
	pulau[0].addPoint(Point(107,116));
	pulau[0].addPoint(Point(112,114));
	pulau[0].addPoint(Point(122,124));
	pulau[0].addPoint(Point(131,132));
	pulau[0].addPoint(Point(140,140));
	pulau[0].addPoint(Point(144,144));
	pulau[0].addPoint(Point(149,143));
	pulau[0].addPoint(Point(157,150));
	pulau[0].addPoint(Point(153,158));
	pulau[0].addPoint(Point(152,164));
	pulau[0].addPoint(Point(159,169));
	pulau[0].addPoint(Point(167,170));
	pulau[0].addPoint(Point(170,182));
	pulau[0].addPoint(Point(174,185));
	pulau[0].addPoint(Point(175,192));
	pulau[0].addPoint(Point(185,191));
	pulau[0].addPoint(Point(191,199));
	pulau[0].addPoint(Point(195,206));
	pulau[0].addPoint(Point(193,212));
	pulau[0].addPoint(Point(190,246));
	pulau[0].addPoint(Point(189,250));
	pulau[0].addPoint(Point(182,245));
	pulau[0].addPoint(Point(181,249));
	pulau[0].addPoint(Point(172,244));
	pulau[0].addPoint(Point(172,251));
	pulau[0].addPoint(Point(172,251));
	pulau[0].addPoint(Point(159,238));
	pulau[0].addPoint(Point(134,219));
	pulau[0].addPoint(Point(130,214));
	pulau[0].addPoint(Point(111,191));
	pulau[0].addPoint(Point(109,184));
	pulau[0].addPoint(Point(100,169));
	pulau[0].addPoint(Point(86,151));
	pulau[0].addPoint(Point(81,148));
	pulau[0].addPoint(Point(77,131));
	pulau[0].addPoint(Point(75,126));
	pulau[0].addPoint(Point(58,115));
	pulau[0].addPoint(Point(56,114));
	pulau[0].addPoint(Point(54,103));
	pulau[0].addPoint(Point(51,103));
	pulau[0].addPoint(Point(41,92));
	pulau[0].addPoint(Point(35,90));
	pulau[0].addPoint(Point(20,74));
	pulau[0].addPoint(Point(16,66));


	pulau[1].addPoint(Point(194,251));
	pulau[1].addPoint(Point(209,253));
	pulau[1].addPoint(Point(210,251));
	pulau[1].addPoint(Point(213,251));
	pulau[1].addPoint(Point(221,256));
	pulau[1].addPoint(Point(230,258));
	pulau[1].addPoint(Point(233,258));
	pulau[1].addPoint(Point(236,262));
	pulau[1].addPoint(Point(239,266));
	pulau[1].addPoint(Point(265,269));
	pulau[1].addPoint(Point(273,259));
	pulau[1].addPoint(Point(276,260));
	pulau[1].addPoint(Point(279,263));
	pulau[1].addPoint(Point(287,263));
	pulau[1].addPoint(Point(301,268));
	pulau[1].addPoint(Point(306,273));
	pulau[1].addPoint(Point(307,278));
	pulau[1].addPoint(Point(315,282));
	pulau[1].addPoint(Point(324,279));
	pulau[1].addPoint(Point(333,282));
	pulau[1].addPoint(Point(332,290));
	pulau[1].addPoint(Point(334,298));
	pulau[1].addPoint(Point(315,292));
	pulau[1].addPoint(Point(312,289));
	pulau[1].addPoint(Point(299,292));
	pulau[1].addPoint(Point(287,291));
	pulau[1].addPoint(Point(267,287));
	pulau[1].addPoint(Point(255,282));
	pulau[1].addPoint(Point(243,281));
	pulau[1].addPoint(Point(238,280));
	pulau[1].addPoint(Point(230,281));
	pulau[1].addPoint(Point(218,278));
	pulau[1].addPoint(Point(204,274));
	pulau[1].addPoint(Point(199,274));
	pulau[1].addPoint(Point(204,269));
	pulau[1].addPoint(Point(189,266));
	pulau[1].addPoint(Point(186,266));
	pulau[1].addPoint(Point(193,258));
	pulau[1].addPoint(Point(196,251));

	pulau[2].addPoint(Point(251,120));
	pulau[2].addPoint(Point(274,127));
	pulau[2].addPoint(Point(283,110));
	pulau[2].addPoint(Point(288,105));
	pulau[2].addPoint(Point(307,101));
	pulau[2].addPoint(Point(327,78));
	pulau[2].addPoint(Point(343,68));
	pulau[2].addPoint(Point(350,68));
	pulau[2].addPoint(Point(353,60));
	pulau[2].addPoint(Point(371,38));
	pulau[2].addPoint(Point(379,34));
	pulau[2].addPoint(Point(383,44));
	pulau[2].addPoint(Point(389,52));
	pulau[2].addPoint(Point(410,63));
	pulau[2].addPoint(Point(407,69));
	pulau[2].addPoint(Point(396,71));
	pulau[2].addPoint(Point(400,78));
	pulau[2].addPoint(Point(385,85));
	pulau[2].addPoint(Point(389,93));
	pulau[2].addPoint(Point(383,97));
	pulau[2].addPoint(Point(393,115));
	pulau[2].addPoint(Point(390,120));
	pulau[2].addPoint(Point(406,134));
	pulau[2].addPoint(Point(403,139));
	pulau[2].addPoint(Point(387,141));
	pulau[2].addPoint(Point(384,158));
	pulau[2].addPoint(Point(381,165));
	pulau[2].addPoint(Point(368,178));
	pulau[2].addPoint(Point(365,198));
	pulau[2].addPoint(Point(362,208));
	pulau[2].addPoint(Point(361,217));
	pulau[2].addPoint(Point(353,215));
	pulau[2].addPoint(Point(336,220));
	pulau[2].addPoint(Point(328,212));
	pulau[2].addPoint(Point(327,205));
	pulau[2].addPoint(Point(321,210));
	pulau[2].addPoint(Point(312,203));
	pulau[2].addPoint(Point(300,206));
	pulau[2].addPoint(Point(292,210));
	pulau[2].addPoint(Point(288,201));
	pulau[2].addPoint(Point(264,200));
	pulau[2].addPoint(Point(258,176));
	pulau[2].addPoint(Point(245,163));
	pulau[2].addPoint(Point(241,146));
	pulau[2].addPoint(Point(246,125));


	pulau[3].addPoint(Point(431,136));
	pulau[3].addPoint(Point(438,136));
	pulau[3].addPoint(Point(441,131));
	pulau[3].addPoint(Point(447,130));
	pulau[3].addPoint(Point(451,134));
	pulau[3].addPoint(Point(459,135));
	pulau[3].addPoint(Point(466,137));
	pulau[3].addPoint(Point(474,137));
	pulau[3].addPoint(Point(479,138));
	pulau[3].addPoint(Point(488,138));
	pulau[3].addPoint(Point(495,135));
	pulau[3].addPoint(Point(500,133));
	pulau[3].addPoint(Point(505,129));
	pulau[3].addPoint(Point(511,125));
	pulau[3].addPoint(Point(512,131));
	pulau[3].addPoint(Point(509,136));
	pulau[3].addPoint(Point(505,141));
	pulau[3].addPoint(Point(495,146));
	pulau[3].addPoint(Point(483,146));
	pulau[3].addPoint(Point(467,143));
	pulau[3].addPoint(Point(466,144));
	pulau[3].addPoint(Point(451,144));
	pulau[3].addPoint(Point(436,144));
	pulau[3].addPoint(Point(431,146));
	pulau[3].addPoint(Point(426,156));
	pulau[3].addPoint(Point(428,163));
	pulau[3].addPoint(Point(435,169));
	pulau[3].addPoint(Point(440,176));
	pulau[3].addPoint(Point(447,173));
	pulau[3].addPoint(Point(451,169));
	pulau[3].addPoint(Point(457,167));
	pulau[3].addPoint(Point(467,164));
	pulau[3].addPoint(Point(479,161));
	pulau[3].addPoint(Point(482,165));
	pulau[3].addPoint(Point(478,169));
	pulau[3].addPoint(Point(471,169));
	pulau[3].addPoint(Point(464,177));
	pulau[3].addPoint(Point(454,183));
	pulau[3].addPoint(Point(448,184));
	pulau[3].addPoint(Point(455,191));
	pulau[3].addPoint(Point(464,202));
	pulau[3].addPoint(Point(464,214));
	pulau[3].addPoint(Point(470,219));
	pulau[3].addPoint(Point(469,225));
	pulau[3].addPoint(Point(452,232));
	pulau[3].addPoint(Point(449,217));
	pulau[3].addPoint(Point(445,215));
	pulau[3].addPoint(Point(440,209));
	pulau[3].addPoint(Point(440,195));
	pulau[3].addPoint(Point(433,200));
	pulau[3].addPoint(Point(430,207));
	pulau[3].addPoint(Point(432,220));
	pulau[3].addPoint(Point(433,233));
	pulau[3].addPoint(Point(428,245));
	pulau[3].addPoint(Point(418,242));
	pulau[3].addPoint(Point(419,227));
	pulau[3].addPoint(Point(419,213));
	pulau[3].addPoint(Point(407,211));
	pulau[3].addPoint(Point(405,196));
	pulau[3].addPoint(Point(412,182));
	pulau[3].addPoint(Point(416,165));

	pulau[4].addPoint(Point(349,306));
	pulau[4].addPoint(Point(341,300));
	pulau[4].addPoint(Point(342,293));
	pulau[4].addPoint(Point(351,292));
	pulau[4].addPoint(Point(359,298));

	pulau[5].addPoint(Point(368,298));
	pulau[5].addPoint(Point(376,300));
	pulau[5].addPoint(Point(373,306));
	pulau[5].addPoint(Point(365,305));


	pulau[6].addPoint(Point(382,300));
	pulau[6].addPoint(Point(388,301));
	pulau[6].addPoint(Point(392,303));
	pulau[6].addPoint(Point(395,303));
	pulau[6].addPoint(Point(395,309));
	pulau[6].addPoint(Point(384,308));
	pulau[6].addPoint(Point(381,309));
	pulau[6].addPoint(Point(377,308));
	pulau[6].addPoint(Point(379,302));

	pulau[7].addPoint(Point(808,209));
	pulau[7].addPoint(Point(792,201));
	pulau[7].addPoint(Point(774,197));
	pulau[7].addPoint(Point(734,181));
	pulau[7].addPoint(Point(722,187));
	pulau[7].addPoint(Point(724,192));
	pulau[7].addPoint(Point(708,193));
	pulau[7].addPoint(Point(708,200));
	pulau[7].addPoint(Point(701,201));
	pulau[7].addPoint(Point(697,211));
	pulau[7].addPoint(Point(682,206));
	pulau[7].addPoint(Point(672,193));
	pulau[7].addPoint(Point(673,175));
	pulau[7].addPoint(Point(671,168));
	pulau[7].addPoint(Point(642,161));
	pulau[7].addPoint(Point(625,168));
	pulau[7].addPoint(Point(621,174));
	pulau[7].addPoint(Point(618,181));
	pulau[7].addPoint(Point(631,182));
	pulau[7].addPoint(Point(637,193));
	pulau[7].addPoint(Point(655,193));
	pulau[7].addPoint(Point(668,192));
	pulau[7].addPoint(Point(668,196));
	pulau[7].addPoint(Point(664,200));
	pulau[7].addPoint(Point(654,197));
	pulau[7].addPoint(Point(648,203));
	pulau[7].addPoint(Point(637,205));
	pulau[7].addPoint(Point(647,211));
	pulau[7].addPoint(Point(649,225));
	pulau[7].addPoint(Point(660,214));
	pulau[7].addPoint(Point(666,207));
	pulau[7].addPoint(Point(668,222));
	pulau[7].addPoint(Point(685,229));
	pulau[7].addPoint(Point(711,237));
	pulau[7].addPoint(Point(732,247));
	pulau[7].addPoint(Point(748,269));
	pulau[7].addPoint(Point(749,280));
	pulau[7].addPoint(Point(740,283));
	pulau[7].addPoint(Point(731,298));
	pulau[7].addPoint(Point(746,300));
	pulau[7].addPoint(Point(760,292));
	pulau[7].addPoint(Point(771,295));
	pulau[7].addPoint(Point(788,312));
	pulau[7].addPoint(Point(809,312));

	pulau[8].addPoint(Point(489,331));
	pulau[8].addPoint(Point(495,322));
	pulau[8].addPoint(Point(499,316));
	pulau[8].addPoint(Point(509,312));
	pulau[8].addPoint(Point(516,309));
	pulau[8].addPoint(Point(523,304));
	pulau[8].addPoint(Point(532,301));
	pulau[8].addPoint(Point(540,301));
	pulau[8].addPoint(Point(547,299));
	pulau[8].addPoint(Point(553,301));
	pulau[8].addPoint(Point(531,313));
	pulau[8].addPoint(Point(523,313));
	pulau[8].addPoint(Point(514,325));

	pulau[9].addPoint(Point(427,304));
	pulau[9].addPoint(Point(442,295));
	pulau[9].addPoint(Point(456,301));
	pulau[9].addPoint(Point(467,303));
	pulau[9].addPoint(Point(477,302));
	pulau[9].addPoint(Point(463,308));

	pulau[10].addPoint(Point(581,209));
	pulau[10].addPoint(Point(575,214));
	pulau[10].addPoint(Point(567,205));
	pulau[10].addPoint(Point(581,203));
	pulau[10].addPoint(Point(590,204));
	pulau[10].addPoint(Point(604,208));
	pulau[10].addPoint(Point(613,214));
	pulau[10].addPoint(Point(612,221));
	pulau[10].addPoint(Point(599,212));
	pulau[10].addPoint(Point(589,214));

	pulau[11].addPoint(Point(570,171));
	pulau[11].addPoint(Point(562,159));
	pulau[11].addPoint(Point(558,146));
	pulau[11].addPoint(Point(557,132));
	pulau[11].addPoint(Point(567,116));
	pulau[11].addPoint(Point(568,131));
	pulau[11].addPoint(Point(563,139));
	pulau[11].addPoint(Point(570,137));
	pulau[11].addPoint(Point(580,129));
	pulau[11].addPoint(Point(576,137));
	pulau[11].addPoint(Point(574,145));
	pulau[11].addPoint(Point(582,152));
	pulau[11].addPoint(Point(568,148));
	pulau[11].addPoint(Point(567,161));

	pulau[12].addPoint(Point(513,189));
	pulau[12].addPoint(Point(510,192));
	pulau[12].addPoint(Point(504,188));
	pulau[12].addPoint(Point(506,182));
	pulau[12].addPoint(Point(516,185));
	pulau[12].addPoint(Point(523,187));
	pulau[12].addPoint(Point(535,184));
	pulau[12].addPoint(Point(538,187));
	pulau[12].addPoint(Point(529,189));
	pulau[12].addPoint(Point(516,189));

	pulau[13].addPoint(Point(179,191));
	pulau[13].addPoint(Point(190,193));
	pulau[13].addPoint(Point(194,203));
	pulau[13].addPoint(Point(203,208));
	pulau[13].addPoint(Point(207,207));
	pulau[13].addPoint(Point(208,201));
	pulau[13].addPoint(Point(200,196));
	pulau[13].addPoint(Point(193,182));
	pulau[13].addPoint(Point(191,186));
	pulau[13].addPoint(Point(187,181));
	pulau[13].addPoint(Point(183,182));

	pulau[14].addPoint(Point(546,222));
	pulau[14].addPoint(Point(535,214));
	pulau[14].addPoint(Point(533,209));
	pulau[14].addPoint(Point(544,208));
	pulau[14].addPoint(Point(551,209));
	pulau[14].addPoint(Point(555,216));
	
	pulau[15].addPoint(Point(48,140));
	pulau[15].addPoint(Point(45,131));
	pulau[15].addPoint(Point(50,132));
	pulau[15].addPoint(Point(58,139));
	pulau[15].addPoint(Point(55,147));

	pulau[16].addPoint(Point(71,171));
	pulau[16].addPoint(Point(69,175));
	pulau[16].addPoint(Point(75,187));
	pulau[16].addPoint(Point(81,184));
	pulau[16].addPoint(Point(74,171));
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
						//fb.clearScreen();
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
						//fb.clearScreen();
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
						//fb.clearScreen();
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
						//fb.clearScreen();
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