#include "Graphics.h"
#include "Texture.h"
#include <IwGx.h>
#include <IwMaterial.h>
#include <IwTexture.h>
#include <Iw2D.h>
#include "ResourceManager.h"
#include "Misc.h"

using namespace GameSDK;

void Graphics::Init()
{
    IwGxInit();
	Iw2DInit();
}

void Graphics::Destroy()
{
	Iw2DTerminate();
    IwGxTerminate();
}

void Graphics::PrepareFrame()
{
    // Clear the screen
	IwGxSetColClear(0xff, 0xff, 0xff, 0xff);
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	IwGxLightingOff();
	Iw2DSetColour(0xFF000000);
	Iw2DFillRect(CIwSVec2(0, 0), CIwSVec2((int16)Misc::GetScreenWidth(), (int16)Misc::GetScreenHeight()));
	IwGxFlush();
}

void Graphics::Redraw()
{
    // Update IwGx state timestamp
    IwGxTickUpdate();

    // End drawing
    IwGxFlush();

    // Swap buffers
    IwGxSwapBuffers();
}

void Graphics::DrawTexture(const Rect& screenCoords, int textureId, const Rect& textureCoord, float xOffset, float yOffset)
{
	static CIwSVec2 textureUVs[4];
	static CIwSVec2 screenXY[4];
	static CIwMaterial material;

	CIwTexture* texture = (CIwTexture*)ResourceManager::GetInstance().GetTexture(textureId)->GetData();
	if (!texture)
		return;

	material.Reset();
	material.SetAlphaMode(CIwMaterial::ALPHA_BLEND);
	material.SetTexture(texture);

	int16 width = texture->GetWidth();
	int16 height = texture->GetHeight();

	static const int16 uvSize = 4096;

	// screen coordinates
	screenXY[0] = CIwSVec2((int16)(screenCoords.left + xOffset), (int16)(screenCoords.top + yOffset));
	screenXY[1] = CIwSVec2((int16)(screenCoords.left + xOffset), (int16)(screenCoords.bottom + yOffset));
    screenXY[2] = CIwSVec2((int16)(screenCoords.right + xOffset), (int16)(screenCoords.top + yOffset));
    screenXY[3] = CIwSVec2((int16)(screenCoords.right + xOffset), (int16)(screenCoords.bottom + yOffset));

	// texture's UV coordinates
	textureUVs[0] = CIwSVec2(((int16)textureCoord.left * uvSize) / width, ((int16)textureCoord.top * uvSize) / height);
	textureUVs[1] = CIwSVec2(((int16)textureCoord.left * uvSize) / width, ((int16)textureCoord.bottom * uvSize) / height);
	textureUVs[2] = CIwSVec2(((int16)textureCoord.right * uvSize) / width, ((int16)textureCoord.top * uvSize) / height);
	textureUVs[3] = CIwSVec2(((int16)textureCoord.right * uvSize) / width, ((int16)textureCoord.bottom * uvSize) / height);

	IwGxSetMaterial(&material);
	IwGxSetUVStream(textureUVs);

	IwGxSetColStream(NULL);
    IwGxSetVertStreamScreenSpace(screenXY, 4);
	IwGxDrawPrims(IW_GX_QUAD_STRIP, NULL, 4);

	IwGxFlush();
}

void Graphics::DrawTexture(const Rect& screenCoords, int textureId, float xOffset, float yOffset)
{
	Texture* texture = ResourceManager::GetInstance().GetTexture(textureId);
	if (!texture)
		return;

	Rect textureCoords;
	textureCoords.left = 0.0f;
	textureCoords.top = 0.0f;
	textureCoords.right = texture->GetWidth();
	textureCoords.bottom = texture->GetHeight();

	DrawTexture(screenCoords, textureId, textureCoords, xOffset, yOffset);
}