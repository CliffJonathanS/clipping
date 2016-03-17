
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <pthread.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <list>
#include <cstring>

#define startx 500
#define starty 500

using namespace std;

static struct termios old;
static struct termios newT;
static int gameover=0;
static int fbfd = 0;
static struct fb_var_screeninfo vinfo;
static struct fb_fix_screeninfo finfo;
static long int screensize = 0;
static char *fbp = 0;
static int a = 2;

static list<int> polygonBound1;
static list<int> polygonBound2;
static list<int> polygonBound3;
static list<int> polygonBound4;
static list<int> polygonBound5;
static list<int> polygonBound6;
static list<int>::iterator it;
static list<int>::iterator itl;

static int charMap[1][5][5] =
{
  //pesawat
  {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},  
  }
};

static int colliderX [5][5];
static int colliderY [5][5];

int x, y;

static long int location = 0;
/****************************
*   CODE TO CREATE 3D box   *
/****************************/

typedef struct {
  float x;
  float y;
  float z;
} point3D;

typedef struct {
  int x;
  int y;
} point2D;

int focal = 10;
static point3D vertex[8];
static point2D orto[8];

//function to see the depth of object from camera prespective
float CamPerspective(float point1, float point2){
    return focal / (focal - point1) * point2;
}

//Matrix multiplication with rotation to get the final coordinate
void Get3DPosition(double theta, double psi){
    double MatrixRotation[3][3] = {
        cos(theta) * sin(psi), sin(theta) * sin(psi), cos(psi),
        sin(theta) * -1 , cos(theta) ,0,
        -cos(theta) * cos(psi) ,-sin(theta) * cos(psi),sin(psi)
    };

    for (int nVertex =0 ; nVertex < 8; nVertex++){
            float tempX = vertex[nVertex].x;
            float tempY = vertex[nVertex].y;
            float tempZ = vertex[nVertex].z;

            vertex[nVertex].x = ((tempX * MatrixRotation[0][0]) + (tempY * MatrixRotation[1][0]) + (tempZ * MatrixRotation[2][0]));
            vertex[nVertex].y = ((tempX * MatrixRotation[0][1]) + (tempY * MatrixRotation[1][1]) + (tempZ * MatrixRotation[2][1]));
            vertex[nVertex].z = ((tempX * MatrixRotation[0][2]) + (tempY * MatrixRotation[1][2]) + (tempZ * MatrixRotation[2][2]));
    }
}

void ShowMatrixRotation(double **MatrixRotation){
  //Show the matrix
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << MatrixRotation[i][j] << " ";
        }
        cout<<endl;
    }
}
/* NOT USED FOR 3D
//Fungsi untuk membuat blok huruf dengan ukuran 5 x 5 blok
void drawPlane(int index,int x,int y, int color){
  int i,j;
  for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++) {
      if (charMap[index][i][j] == 1){
        drawColor(x*10 + (j * 5),420 + (i * 5)-y*5, color);
        colliderX[i][j] = x*10 + (j * 5);
        colliderY[i][j] = 420 + (i * 5)-y*5;
      } else {
        drawColor(x*10 + (j * 5),420 + (i * 5)-y*5, 0, 0, 0);
        colliderX[i][j] = -1;
        colliderY[i][j] = -1;
      }
    }
  } 
}

void erasePlane(int index,int x,int y){
  int i,j;
  for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++) {
      drawColor(x*10 + (j * 5) ,420 + (i * 5)-y*5, 0, 0, 0);
    }
  } 

}
*/

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  newT = old; /* make new settings same as old settings */
  newT.c_lflag &= ~ICANON; /* disable buffered i/o */
  newT.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &newT); /* use these new terminal i/o settings now */
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



void drawColor(int a , int b, int colorR, int colorG, int colorB){
	int x = 0, y = 0;
	for (y = b; y < b+2; y++)
        for (x = a; x < a+2; x++) {

            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = colorB;// Some blue
                *(fbp + location + 1) = colorG;// A little green
                *(fbp + location + 2) = colorR;// A lot of red
                *(fbp + location + 3) = 0;      // No transparency
            } 
        }
}

void line(int x0, int y0, int x1, int y1, int colorR, int colorG, int colorB) {

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;

  while(1){
    drawColor(x0,y0,colorR,colorG,colorB);
    int q,w;
    for(q=0;q<5;q++){
    for(w=0;w<5;w++){
        if ((x0==colliderX[q][w]) && (y0==colliderY[q][w])){
          gameover=1;
        }
    }
  }
  if ((x0==x1 && y0==y1) || (x0==0) || (y0==0)) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void boundaries(int x0, int y0, int x1, int y1, list<int> *polygonBound) {

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;
  point2D tempPoint;
  while(1){
    //tempPoint.x = x0; tempPoint.y = y0;
    //cout << tempPoint.x << "   " << tempPoint.y << endl;
    polygonBound->push_back(x0);
    polygonBound->push_back(y0);

    int q,w;
    
    if ((x0==x1 && y0==y1) || (x0==0) || (y0==0)) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void startScreen(){
	 // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    //printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (atoi(fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    //printf("The framebuffer device was mapped to memory successfully.\n");

	int i,j;
	
	for (i = 0; i < 700; i++){
        for (j = 0; j < 1300; j++) {
			location = (j+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (i+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 0;//100;        // Some blue
                *(fbp + location + 1) = 0;//15+(x-100)/2;     // A little green
                *(fbp + location + 2) = 0;//200-(y-100)/5;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
        //location += 4;
            } 
            else  { //assume 16bpp
                int b = 0;//10;
                int g = 0;//(x-100)/6;     // A little green
                int r = 0;//31-(y-100)/16;    // A lot of red
                unsigned short int t = r | g | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
		}
	}
} 
/* NOT USED FOR 3D
void *movePlane()
{
  while(1){
    int q;
    //Animation move right  
    for (q=0;q<100;q++){
      erasePlane(0,q,62);
      drawPlane(0,q+1,62,255);
      usleep(100000);
    }
    //Animation move left   
    for (q=100;q>0;q--){
      erasePlane(0,q+1,62);
      drawPlane(0,q,62,255);
      usleep(100000);
    }
  }
  return NULL;
}
/* NOT USED for 3D
void drawBoundary() {
  int pointx, pointy;
  float angle;
  double pi = acos(-1);
  float leftangle, rightangle;

  rightangle = -pi/4;
  leftangle = -(3*pi)/4;
  angle = rightangle;
  for (angle = leftangle; angle < rightangle; angle += 0.0174) {
    pointx = (int) 20*cos(angle);
    pointy = (int) 20*sin(angle);
    //line(startx, starty, startx+pointx, starty+pointy, 100);
  }
}
*/

/* NOT USED for 3D
void *getchthread()
{
  int pointx, pointy;
  float angle;
  double pi = acos(-1);
  
  drawBoundary();

  angle = -pi/2;
  pointx = (int) 20*cos(angle);
  pointy = (int) 20*sin(angle);
  line(startx, starty, startx+pointx, starty+pointy, 255);
  //double rotation_angle = (double) angle / 180.0 * pi;
  while(1){
      char c;
      printf("Letter : ");
      c = getch();
      printf("\nYou typed: %c\n", c);
      switch (c) {  
        case 32 :
          line(startx, starty, startx+40*pointx, starty+40*pointy, 255);
          usleep(100000);
          line(startx, starty, startx+40*pointx, starty+40*pointy, 0);
          line(startx, starty, startx+pointx, starty+pointy, 255);
          if(gameover==1){
            printf("gameover");
          }
          break;
        case 'a' :
        case 'A' :
          if (angle > -(3*pi)/4) {
            line(startx, starty, startx+pointx, starty+pointy, 0);
            pointx = (int) 20*cos(angle);
            pointy = (int) 20*sin(angle);
            drawBoundary();
            line(startx, starty, startx+pointx, starty+pointy, 255);
            angle -= 0.0174;
            printf("%d\n", x);
          }
          break;
        case 'd' :
        case 'D' :
          if (angle < -pi/4) {
            line(startx, starty, startx+pointx, starty+pointy, 0);
            pointx = (int) 20*cos(angle);
            pointy = (int) 20*sin(angle);
            drawBoundary();
            line(startx, starty, startx+pointx, starty+pointy, 255);
            angle += 0.0174;
            printf("%d\n", x);
          }
          break;
      }
    }
  return NULL;

}
*/
void ConvertVertexToOrto(){
  //Show the array of vertex
    /*cout << "AFTER rotation" <<endl;
    for (int nVertex =0 ; nVertex < 8; nVertex++){
        cout << "x: "<< vertex[nVertex].x << " y: " << vertex[nVertex].y << " z: " << vertex[nVertex].z<< endl;
    }*/

    for (int nVertex =0 ; nVertex < 8; nVertex++){
      
        orto[nVertex].x = (int) (CamPerspective(vertex[nVertex].z, vertex[nVertex].x ) * 50) + 400;
        orto[nVertex].y = (int) (CamPerspective(vertex[nVertex].z, vertex[nVertex].y ) * 50) + 400;
    }

}

void DrawAndCheckBoundaries(){
  //Show the array of orthogonal point
    /*cout << "ORTO" <<endl;
    for (int nVertex =0 ; nVertex < 8; nVertex++){
        cout << "orto :" << nVertex<<" x: "<< orto[nVertex].x << " y: " << orto[nVertex].y << endl;
    }*/

    //draw the 4 lines of cubes bottom 
    for (int i = 0; i < 4 ; i++){
      int next = i+1;
      if (next < 4){
        line(orto[i].x,orto[i].y,orto[i+1].x,orto[i+1].y,255,255,255);
        boundaries(orto[i].x,orto[i].y,orto[i+1].x,orto[i+1].y,&polygonBound6);
      } else {
        line(orto[i].x,orto[i].y,orto[0].x,orto[0].y, 255, 255, 255);
        boundaries(orto[i].x,orto[i].y,orto[0].x,orto[0].y,&polygonBound6);
      }

    }


    //draw the 4 lines of cubes upper
    for (int i = 4; i < 8 ; i++){
      int next = i+1;
      if (next < 8){
        line(orto[i].x,orto[i].y,orto[i+1].x,orto[i+1].y,255,255,255);
        boundaries(orto[i].x,orto[i].y,orto[i+1].x,orto[i+1].y,&polygonBound5);
      } else {
        line(orto[i].x,orto[i].y,orto[4].x,orto[4].y, 255, 255, 255);
        boundaries(orto[i].x,orto[i].y,orto[4].x,orto[4].y,&polygonBound5);
      }

    }

    //draw the 4 lines of cubes height
    for (int i = 0; i < 4 ; i++){
      int next = i+1;
      if (next < 4){
        line(orto[i].x,orto[i].y,orto[i+4].x,orto[i+4].y,255,255,255);
      } else {
        line(orto[i].x,orto[i].y,orto[7].x,orto[7].y, 255, 255, 255);
      }
    }
     //boundaries for polygon4
    boundaries(orto[2].x,orto[2].y,orto[1].x,orto[1].y,&polygonBound4);
    boundaries(orto[1].x,orto[1].y,orto[5].x,orto[5].y,&polygonBound4);
    boundaries(orto[5].x,orto[5].y,orto[6].x,orto[6].y,&polygonBound4);
    boundaries(orto[6].x,orto[6].y,orto[2].x,orto[2].y,&polygonBound4);

    //boundaries for polygon3
    boundaries(orto[0].x,orto[0].y,orto[1].x,orto[1].y,&polygonBound3);
    boundaries(orto[1].x,orto[1].y,orto[5].x,orto[5].y,&polygonBound3);
    boundaries(orto[5].x,orto[5].y,orto[4].x,orto[4].y,&polygonBound3);
    boundaries(orto[4].x,orto[4].y,orto[0].x,orto[0].y,&polygonBound3);

    //boundaries for polygon2
    boundaries(orto[0].x,orto[0].y,orto[3].x,orto[3].y,&polygonBound2);
    boundaries(orto[3].x,orto[3].y,orto[7].x,orto[7].y,&polygonBound2);
    boundaries(orto[7].x,orto[7].y,orto[4].x,orto[4].y,&polygonBound2);
    boundaries(orto[4].x,orto[4].y,orto[0].x,orto[0].y,&polygonBound2);

    //boundaries for polygon1
    boundaries(orto[2].x,orto[2].y,orto[3].x,orto[3].y,&polygonBound1);
    boundaries(orto[3].x,orto[3].y,orto[7].x,orto[7].y,&polygonBound1);
    boundaries(orto[7].x,orto[7].y,orto[6].x,orto[6].y,&polygonBound1);
    boundaries(orto[6].x,orto[6].y,orto[2].x,orto[2].y,&polygonBound1);

    //sort the vertex from most positif bubble sort
    //point2D tempBiggestZ = vertex[0].z;
    point3D swap;
    
	int i = 0;
	point3D sortedVertex[8];
	memcpy(&sortedVertex,&vertex,sizeof(vertex));

	cout<<endl;
    while (i<8) {
		if (sortedVertex[i].z < sortedVertex[i+1].z) {
			swap = sortedVertex[i]; 
			sortedVertex[i] = sortedVertex[i+1]; 
			sortedVertex[i+1] = swap; 
			if (i) i--;
		}
		else
			i++; 
	}
	point2D sortedOrto[8];
	for (int nVertex =0 ; nVertex < 8; nVertex++){ 
        sortedOrto[nVertex].x = (int) (CamPerspective(sortedVertex[nVertex].z, sortedVertex[nVertex].x ) * 50) + 400;
        sortedOrto[nVertex].y = (int) (CamPerspective(sortedVertex[nVertex].z, sortedVertex[nVertex].y ) * 50) + 400;
    }/*
	for(int i=0;i<8;i++){
		cout << "SORT x :" <<sortedOrto[i].x << " y: " <<sortedOrto[i].y ;
	}
	cout<<"\n";
	for(int i=0;i<8;i++){
		cout << "ORTO x :" <<orto[i].x << " y: " <<orto[i].y ;
	}
	cout<<"\n";
	*/
	//from sortedVertex find the polygon which has those vertex. This will determine the priority of filling polygon
	list<int> prioritasPolygon;
	for (int j = 0; j < 8; j ++){

		bool TrueX = false,TrueY =false;
		for (it = polygonBound1.begin(); it != polygonBound1.end(); it++){
			//check x element
			if ((*it) % 2 == 0){
				
				if  ((*it) == sortedOrto[j].x){
					//cout << "WOI";
					TrueX = true;
				}
			} else {
				if  ((*it) == sortedOrto[j].y){
					//cout << "WOI";
					TrueY = true;
				}

			}

			if (TrueY && TrueX ) {
				//cout << "WOI";
				prioritasPolygon.push_back(1);
				break;
			}
		}	
		TrueX = false,TrueY =false;
		for (it = polygonBound2.begin(); it != polygonBound2.end(); it++){
			//check x element
			if ((*it) % 2 == 0){
				
				if  ((*it) == sortedOrto[j].x){
					//cout << "WOI";
					TrueX = true;
				}
			} else {
				if  ((*it) == sortedOrto[j].y){
					//cout << "WOI";
					TrueY = true;
				}

			}

			if (TrueY && TrueX ) {
				//cout << "WOI";
				prioritasPolygon.push_back(2);
				break;
			}
		}
		TrueX = false,TrueY =false;
		for (it = polygonBound3.begin(); it != polygonBound3.end(); it++){
			//check x element
			if ((*it) % 2 == 0){
				
				if  ((*it) == sortedOrto[j].x){
					//cout << "WOI";
					TrueX = true;
				}
			} else {
				if  ((*it) == sortedOrto[j].y){
					//cout << "WOI";
					TrueY = true;
				}

			}

			if (TrueY && TrueX ) {
				//cout << "WOI";
				prioritasPolygon.push_back(3);
				break;
			}
		}

		TrueX = false,TrueY =false;
		for (it = polygonBound4.begin(); it != polygonBound4.end(); it++){
			//check x element
			if ((*it) % 2 == 0){
				
				if  ((*it) == sortedOrto[j].x){
					//cout << "WOI";
					TrueX = true;
				}
			} else {
				if  ((*it) == sortedOrto[j].y){
					//cout << "WOI";
					TrueY = true;
				}

			}

			if (TrueY && TrueX ) {
				//cout << "WOI";
				prioritasPolygon.push_back(4);
				break;
			}
		}					
		TrueX = false,TrueY =false;
		for (it = polygonBound5.begin(); it != polygonBound5.end(); it++){
			//check x element
			if ((*it) % 2 == 0){
				
				if  ((*it) == sortedOrto[j].x){
					//cout << "WOI";
					TrueX = true;
				}
			} else {
				if  ((*it) == sortedOrto[j].y){
					//cout << "WOI";
					TrueY = true;
				}

			}

			if (TrueY && TrueX ) {
				//cout << "WOI";
				prioritasPolygon.push_back(5);
				break;
			}
		}

		TrueX = false,TrueY =false;
		for (it = polygonBound6.begin(); it != polygonBound6.end(); it++){
			//check x element
			if ((*it) % 2 == 0){
				
				if  ((*it) == sortedOrto[j].x){
					//cout << "WOI";
					TrueX = true;
				}
			} else {
				if  ((*it) == sortedOrto[j].y){
					//cout << "WOI";
					TrueY = true;
				}

			}

			if (TrueY && TrueX ) {
				//cout << "WOI";
				prioritasPolygon.push_back(6);
				break;
			}
		}
	}	

	/*for (it = prioritasPolygon.begin(); it != prioritasPolygon.end(); it++){
		cout << *it << " ";
	}*/
	//Filling the polygon there are 6 polygons to be filled 
	//  Fill the pixels between node pairs.
	for (int i=200; i<700; i++) {
		for (int j=200; j<700; j++) {
			bool isFilled = false, startColor = false;
			for (it = prioritasPolygon.begin(); it != prioritasPolygon.end(); it++){
				if ((*it) == 1) {
					bool TrueX = false, TrueY = false;
					for (itl = polygonBound1.begin(); itl != polygonBound1.end(); itl++){
						//check x element
            int xExtreme, yExtreme;
						if ((*itl) % 2 == 0){
							
							if  ((*itl) == j){
								//cout << "WOI";
								TrueX = true;
                xExtreme = j;
							}
						} else if  ((*itl) == i && TrueX){
                //cout << "WOI";
                TrueY = true;
                yExtreme = i;
            } else {
							 TrueX = false;

						}

						if (TrueY && TrueX && !startColor ) {
							//cout << "WOI";
							startColor = true;
							
						} else if (TrueY && TrueX && startColor){
							startColor = false;
						}

						if(startColor && !isFilled & TrueY){
							//fill with red
              if (i>xExtreme && j > yExtreme){
                drawColor(i,j,255,0,0);
                startColor = false;  
              }
							
							isFilled = true;
						}

					} 

				} else if ((*it) == 2) {
          bool TrueX = false, TrueY = false;
					//cout << 2 <<endl;
				} else if ((*it) == 3) {
					//cout << 3 <<endl;
				} else if ((*it) == 4) {
					//cout << 4 <<endl;
				} else if ((*it) == 5) {
					//cout << 5 <<endl;
				} else if ((*it) == 6) {
					//cout << 6 <<endl;
				}
			}
		}
	}
	
}

int main()
{

   x = 0;
   y = 0;
   double rTheta = 0, rPsi = 0;
	startScreen();
  
  //line(0,0,500,500);
    
  /*pthread_t pthread;
	char ch = "";
	if (pthread_create(&pthread, NULL, getchthread,&ch)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

  pthread_t tidpesawat;
  if (pthread_create(&tidpesawat, NULL, movePlane, NULL)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }

	while(!gameover);
	printf("finished\n");

	/* wait for the second thread to finish */
	/*if(pthread_join(getchthread, NULL)) {

	fprintf(stderr, "Error joining thread\n");
	return 2;

	}
	printf("typed: %c \n", &ch);
  	return 0;*/

	//CGraphics using orthogonal view of dots
    cout << "Hello world!" << endl;
    //this is the coordinate of 3d point relatif to origin 0,0,0
    
    

    
/***********************************************
* INSTATIATION OF CUBE                         *
************************************************/

    //BOTTOM PART OF CUBE y is MINUS
    //righmost back bottom
    vertex[0].x = -a;
    vertex[0].y = -a;
    vertex[0].z = -a;
    //righmost front bottom
    vertex[1].x = a;
    vertex[1].y = -a;
    vertex[1].z = -a;
    //leftmost front bottom
    vertex[2].x = a;
    vertex[2].y = -a;
    vertex[2].z = a;
    //leftmost back bottom
    vertex[3].x = -a;
    vertex[3].y = -a;
    vertex[3].z = a;
    //UPPER PART OF CUBE y is POSITIF
    //righmost back upper
    vertex[4].x = -a;
    vertex[4].y = a;
    vertex[4].z = -a;
    //righmost front upper
    vertex[5].x = a;
    vertex[5].y = a;
    vertex[5].z = -a;
    //leftmost front upper
    vertex[6].x = a;
    vertex[6].y = a;
    vertex[6].z = a;
    //leftmost back upper
    vertex[7].x = -a;
    vertex[7].y = a;
    vertex[7].z = a;

    //Loop for animation
    for (rPsi = 0; rPsi < 1 ; rPsi + 0.1){

      rTheta = 1;
      Get3DPosition(rTheta,rPsi);

      ConvertVertexToOrto();
      DrawAndCheckBoundaries();
      

      for (it = polygonBound1.begin(); it != polygonBound1.end(); it++){
        if ((*it) % 2 == 0){
          //cout << "Poly bound x:" << *it;
        } else{
          //cout << " y : " << *it << endl;
        }
      }

      sleep(1);
      startScreen();
    }
	   
    // Figure out where in memory to put the pixel
    
	   munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
