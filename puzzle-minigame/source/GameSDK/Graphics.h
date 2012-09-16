#ifndef GAMESDK_GRAPHICS_H
#define GAMESDK_GRAPHICS_H

#include "../MiniGameInterface.h"

namespace GameSDK
{
	class Graphics
	{
	public:
		static void Init();
		static void Destroy();

		static void PrepareFrame();
		static void Redraw();

		static void DrawTexture(const Rect& screenCoords, int textureId, const Rect& textureCoord, float xOffset = 0.0f, float yOffset = 0.0f);
		static void DrawTexture(const Rect& screenCoords, int textureId, float xOffset = 0.0f, float yOffset = 0.0f);
	};
}

#endif
