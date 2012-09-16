#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <IwTexture.h>

struct Point
{
	int x;
	int y;
};

class Graphics
{
public:
	static void init();
	static void destroy();
	static void prepareFrame();
	static void redraw();
	static int getScreenWidth();
	static int getScreenHeight();
	static void drawTexture(CIwTexture* texture,
							const Point& p0, const Point& p1, const Point& p2, const Point& p3,
							const Point& t0, const Point& t1, const Point& t2, const Point& t3);
	static void drawTexture(CIwTexture* texture,
							const Point& p0, const Point& p1, const Point& p2, const Point& p3);
	static void drawTexture(CIwTexture* texture, const Point& center, int w, int h, int offset, float angle, const Point& t0, const Point& t1, const Point& t2, const Point& t3);
	static void drawTexture(CIwTexture* texture, int x, int y);
	static void drawFrame(CIwTexture* texture, const Point& center, int w, int h, int offset, float angle, int frame, int frameNumber);
};

#endif