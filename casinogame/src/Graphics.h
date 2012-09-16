#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "ResourceManager.h"

class Graphics
{
public:
    Graphics(int* argc, char* argv[], const char* windowName);
    virtual ~Graphics();

    static void beginFrame();
    static void endFrame();
    static void redraw();

    static void drawTexture(const char* textureName, int x, int y, int width, int height);
    static void drawTexture(const char* textureName, int x, int y, int width, int height, int frame, int frames);

    static void setClip(int x, int y, int width, int height);
    static void resetClip();

    static int screenWidth();
    static int screenHeight();
};

#endif
