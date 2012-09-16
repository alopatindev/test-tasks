#include "Graphics.h"
#include <IwGx.h>
#include <IwMaterial.h>
#include <IwTexture.h>
#include <Iw2D.h>
#include <cmath>

void Graphics::init()
{
    IwGxInit();
	Iw2DInit();
}

void Graphics::destroy()
{
	Iw2DTerminate();
    IwGxTerminate();
}

void Graphics::prepareFrame()
{
    // Clear the screen
	IwGxSetColClear(0xff, 0xff, 0xff, 0xff);
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	//IwGxLightingOn();
	Iw2DSetColour(0xFF000000);
	Iw2DFillRect(CIwSVec2(0, 0), CIwSVec2(getScreenWidth(), getScreenHeight()));
	IwGxFlush();
}

void Graphics::redraw()
{
    // Update IwGx state timestamp
    IwGxTickUpdate();

    // End drawing
    IwGxFlush();

    // Swap buffers
    IwGxSwapBuffers();
}

void Graphics::drawTexture(CIwTexture* texture,
						   const Point& p0, const Point& p1, const Point& p2, const Point& p3,
						   const Point& t0, const Point& t1, const Point& t2, const Point& t3)
{
	static CIwSVec2 textureUVs[4];
	static CIwSVec2 screenXY[4];
	static CIwMaterial material;

	if (!texture)
		return;

	material.Reset();
	material.SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	material.SetTexture(texture);

	int16 tWidth = texture->GetWidth();
	int16 tHeight = texture->GetHeight();

	static const int16 uvSize = 4096;

	// screen coordinates
	screenXY[0] = CIwSVec2(p0.x, p0.y);
	screenXY[1] = CIwSVec2(p1.x, p1.y);
    screenXY[2] = CIwSVec2(p2.x, p2.y);
    screenXY[3] = CIwSVec2(p3.x, p3.y);

	// texture's UV coordinates
	textureUVs[0] = CIwSVec2((t0.x * uvSize) / tWidth, (t0.y * uvSize) / tHeight);
	textureUVs[1] = CIwSVec2((t1.x * uvSize) / tWidth, (t1.y * uvSize) / tHeight);
	textureUVs[2] = CIwSVec2((t2.x * uvSize) / tWidth, (t2.y * uvSize) / tHeight);
	textureUVs[3] = CIwSVec2((t3.x * uvSize) / tWidth, (t3.y * uvSize) / tHeight);

	IwGxSetMaterial(&material);
	IwGxSetUVStream(textureUVs);

	IwGxSetColStream(NULL);
    IwGxSetVertStreamScreenSpace(screenXY, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);

	IwGxFlush();
}

void Graphics::drawTexture(CIwTexture* texture,
						   const Point& p0, const Point& p1, const Point& p2, const Point& p3)
{
	Point uv[4];
	uv[0].x = 0;
	uv[0].y = 0;
	uv[1].x = 0;
	uv[1].y = texture->GetHeight();
	uv[2].x = texture->GetWidth();
	uv[2].y = 0;
	uv[3].x = texture->GetWidth();
	uv[3].y = texture->GetHeight();
	drawTexture(texture, p0, p1, p2, p3, uv[0], uv[1], uv[2], uv[3]); 
}

void Graphics::drawTexture(CIwTexture* texture, int x, int y)
{
	Point p[4];
	p[0].x = x;	p[0].y = y;
	p[1].x = x; p[1].y = texture->GetHeight() + y;
	p[2].x = texture->GetWidth() + x; p[2].y = y;
	p[3].x = texture->GetWidth() + x; p[3].y = texture->GetHeight() + y;
	drawTexture(texture, p[0], p[1], p[2], p[3]);
}

// draw frameNum of frames
void Graphics::drawTexture(CIwTexture* texture, const Point& center, int w, int h, int offset, float angle, const Point& t0, const Point& t1, const Point& t2, const Point& t3)
{
	Point v[4];
	Point uv[4];

	angle -= M_PI/2;

	float sint = sinf(angle);
	float cost = cosf(angle);

    v[0].x = center.x + (offset + h) * cost - (-w/2) * sint;
    v[0].y = center.y + (offset + h) * sint + (-w/2) * cost;

    v[1].x = center.x + offset * cost - (-w/2) * sint;
    v[1].y = center.y + offset * sint + (-w/2) * cost;

    v[2].x = center.x + (offset + h) * cost - w/2 * sint;
    v[2].y = center.y + (offset + h) * sint + w/2 * cost;

    v[3].x = center.x + offset * cost - w/2 * sint;
    v[3].y = center.y + offset * sint + w/2 * cost;

	drawTexture(texture, v[0], v[1], v[2], v[3], t0, t1, t2, t3);
}

void Graphics::drawFrame(CIwTexture* texture, const Point& center, int w, int h, int offset, float angle, int frame, int frameNumber)
{
	int frameWidth = texture->GetWidth() / frameNumber;
	Point uv[4];
	uv[0].x = frame * frameWidth;
	uv[0].y = 0;
	uv[1].x = frame * frameWidth;
	uv[1].y = texture->GetHeight();
	uv[2].x = (frame + 1) * frameWidth;
	uv[2].y = 0;
	uv[3].x = (frame + 1) * frameWidth;
	uv[3].y = texture->GetHeight();
	drawTexture(texture, center, w, h, offset, angle, uv[0], uv[1], uv[2], uv[3]);
}

int Graphics::getScreenWidth()
{
	return IwGxGetDisplayWidth();
}

int Graphics::getScreenHeight()
{
	return IwGxGetDisplayHeight();
}