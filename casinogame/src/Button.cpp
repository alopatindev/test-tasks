#include "Button.h"
#include "Graphics.h"

Button::Button(int x, int y, int width, int height, const char* textureName)
    : x(x), y(y),
      width(width), height(height),
      textureName(textureName),
      enabled(true)
{
}

Button::~Button()
{
}

void Button::render() const
{
    if (!enabled)
        Graphics::drawTexture(textureName.c_str(), x, y, width, height, 0, 3);
    else
        Graphics::drawTexture(textureName.c_str(), x, y, width, height, 2, 3);
}
