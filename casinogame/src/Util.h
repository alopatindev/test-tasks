#ifndef UTIL_H

#include "Button.h"

namespace Util {
    bool pointInRect(int x0, int y0, int x, int y, int width, int height)
    {
        return x0 >= x && x0 <= x + width &&
               y0 >= y && y0 <= y + height;
    }

    bool pointInRect(int x0, int y0, const Button* rect)
    {
        return pointInRect(x0, y0, rect->getX(), rect->getY(),
                                   rect->getWidth(), rect->getHeight());
    }
}

#endif
