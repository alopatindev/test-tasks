#ifndef BUTTON_H
#define BUTTON_H

#include "ResourceManager.h"
#include <string>

class Button
{
    bool enabled;
    Texture* texture;
    std::string textureName;
    int x, y, width, height;

public:
    Button(int x, int y, int width, int height, const char* textureName);
    virtual ~Button();
    void render() const;
    bool getEnabled()
    {
        return enabled;
    }
    void setEnabled(bool enabled = true)
    {
        this->enabled = enabled;
    }
    void setCoords(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    int getWidth() const
    {
        return width;
    }
    int getHeight() const
    {
        return height;
    }
};

#endif
