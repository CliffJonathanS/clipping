#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <vector>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <pthread.h>
#include <math.h>

using namespace std;

class Color {
	public:
		// ctor, cctor, dtor
		Color();
		Color(int, int, int);
		Color(const Color&);
		~Color();

		// getter
		int getR();
		int getG();
		int getB();

		// setter
		void setR(int);
		void setG(int);
		void setB(int);

		// operator=
		Color& operator=(const Color&);
	private:
		int R, G, B;
};

class Point {
	public:
		// ctor, cctor, dtor
		Point(float, float);
		Point(const Point&);
		~Point();

		// getter
		float getX();
		float getY();

		// setter
		void setX(float);
		void setY(float);

		// operator=
		Point& operator=(const Point&);
		Point& rotate(float angle, Point pusat);
	private:
		float X, Y;

};

class Polygon {
	public:
		// ctor, cctor, dtor
		Polygon();
		Polygon(const Polygon&,int);
		~Polygon();

		// getter
		int getPriority();
		Point getPoint(int);
		vector<Point> getPoints();
		float getLeft();
		float getRight();
		float getTop();
		float getBottom();
		Color getColor();

		// setter
		void setPriority(int);
		void setPoint(int, Point);
		void setColor(Color);

		// method
		void addPoint(Point);

		// operator=
		Polygon& operator=(const Polygon&);
	private:
		vector<Point> points;
		int priority;
		Color pcolor;
};

class FrameBuffer {
	public:
		// ctor, dtor
		FrameBuffer();
		~FrameBuffer();

		// getter
		int getScreenWidth();
		int getScreenHeight();
		
		// methods
		void clearScreen();
		void drawPoint(Point, Color);
		bool clipPoint(Point, Color);
		void drawLine(Point, Point, Color);
		void drawPolygon(Polygon, Color); // draw wireframe
		void fillPolygon(Polygon, Color);
		
		void anticlip(Polygon* , int);

	private:
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;
		long int screensize;
		char *display;
		int fdScreen;
};