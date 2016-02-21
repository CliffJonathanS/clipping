#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <vector>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

using namespace std;

class Color {
	public:
		// ctor, cctor, dtor
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
		Point(int, int);
		Point(const Point&);
		~Point();

		// getter
		int getX();
		int getY();

		// setter
		void setX(int);
		void setY(int);

		// operator=
		Point& operator=(const Point&);
	private:
		int X, Y;

};

class Polygon {
	public:
		// ctor, cctor, dtor
		Polygon();
		Polygon(const Polygon&);
		~Polygon();

		// getter
		Point getPoint(int);
		vector<Point> getPoints();

		// setter
		void setPoint(int, Point);

		// method
		void addPoint(Point);

		// operator=
		Polygon& operator=(const Polygon&);
	private:
		vector<Point> points;
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
		void drawLine(Point, Point, Color);
		void drawPolygon(Polygon, Color); // draw wireframe
		void fillPolygon(Polygon, Color);

	private:
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;
		long int screensize;
		char *display;
		int fdScreen;
};