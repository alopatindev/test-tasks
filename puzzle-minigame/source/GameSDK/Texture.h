#ifndef GAMESDK_TEXTURE_H
#define GAMESDK_TEXTURE_H

#include <IwTexture.h>

namespace GameSDK
{
	class Texture
	{
		CIwTexture* texture;

	public:
		Texture()
		{
		}

		virtual ~Texture()
		{
			if (texture)
				delete texture;
		}

		float GetWidth() const
		{
			return (float)texture->GetWidth();
		}
		float GetHeight() const
		{
			return (float)texture->GetHeight();
		}

		const void* GetData() const
		{
			return (void *)texture;
		}

		void SetData(void* data)
		{
			texture = (CIwTexture*)data;
		}
	};
}

#endif