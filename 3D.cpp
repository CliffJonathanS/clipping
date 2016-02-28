
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

float CamPerspective(float point1, float point2){
    return focal / (focal - point1) * point2;
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

void startScreen(){
	 // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

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

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (atoi(fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

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


int main()
{

   x = 0;
   y = 0;
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
    int a = 2;
    double theta = 0;
    double psi = 0;
    double MatrixRotation[3][3] = {
        cos(theta) * sin(psi), sin(theta) * sin(psi), cos(psi),
        sin(theta) * -1 , cos(theta) ,0,
        -cos(theta) * cos(psi) ,-sin(theta) * cos(psi),sin(psi)
    };
    //Show the matrix
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << MatrixRotation[i][j] << " ";
        }
        cout<<endl;
    }

    point3D vertex[8];
    point2D orto[8];
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

    //Show the array of vertex
    cout << "Before rotation" <<endl;
    for (int nVertex =0 ; nVertex < 8; nVertex++){
        cout << "x: "<< vertex[nVertex].x << " y: " << vertex[nVertex].y << " z: " << vertex[nVertex].z << endl;
    }
    //Matrix multiplication with rotation to get the final coordinate

    for (int nVertex =0 ; nVertex < 8; nVertex++){
            float tempX = vertex[nVertex].x;
            float tempY = vertex[nVertex].y;
            float tempZ = vertex[nVertex].z;

            vertex[nVertex].x = ((tempX * MatrixRotation[0][0]) + (tempX * MatrixRotation[1][0]) + (tempX * MatrixRotation[2][0]));
            vertex[nVertex].y = ((tempY * MatrixRotation[0][1]) + (tempY * MatrixRotation[1][1]) + (tempY * MatrixRotation[2][1]));
            vertex[nVertex].z = ((tempZ * MatrixRotation[0][2]) + (tempZ * MatrixRotation[1][2]) + (tempZ * MatrixRotation[2][2]));

    }

    //Show the array of vertex
    cout << "AFTER rotation" <<endl;
    for (int nVertex =0 ; nVertex < 8; nVertex++){
        cout << "x: "<< vertex[nVertex].x << " y: " << vertex[nVertex].y << " z: " << vertex[nVertex].z<< endl;
    }

    for (int nVertex =0 ; nVertex < 8; nVertex++){
        orto[nVertex].x = (int) (CamPerspective(vertex[nVertex].z, vertex[nVertex].x ) * 100) + 400;
        orto[nVertex].y = (int) (CamPerspective(vertex[nVertex].z, vertex[nVertex].y ) * 100) + 400;
    }

    //Show the array of orthogonal point
    cout << "ORTO" <<endl;
    for (int nVertex =0 ; nVertex < 8; nVertex++){
        cout << "orto :" << nVertex<<" x: "<< orto[nVertex].x << " y: " << orto[nVertex].y << endl;
    }
    //draw the 4 lines of cubes bottom 
    for (int i = 0; i < 4 ; i++){
      int next = i+1;
      if (next < 4){
        line(orto[i].x,orto[i].y,orto[i+1].x,orto[i+1].y,255,255,255);
      } else {
        line(orto[i].x,orto[i].y,orto[0].x,orto[0].y, 255, 255, 255);
      }

    }


    //draw the 4 lines of cubes upper
    for (int i = 4; i < 8 ; i++){
      int next = i+1;
      if (next < 8){
        line(orto[i].x,orto[i].y,orto[i+1].x,orto[i+1].y,255,255,255);
      } else {
        line(orto[i].x,orto[i].y,orto[4].x,orto[4].y, 255, 255, 255);
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
	
    // Figure out where in memory to put the pixel
    
	   munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
