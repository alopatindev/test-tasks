#ifndef GAMESDK_RESOURCEMANAGER_H
#define GAMESDK_RESOURCEMANAGER_H

#include "Singleton.h"
#include "Texture.h"
#include <vector>
#include <string>

namespace GameSDK
{
	class ResourceManagerClass
	{
		typedef std::pair<std::string, Texture*> TexturePair;
		std::vector< TexturePair > textures;

	public:
		ResourceManagerClass();
		virtual ~ResourceManagerClass();

		void AddTexture(const char * filename);
		void LoadTextures();
		void DestroyTextures();

		Texture* GetTexture(int id) const;
	};

	typedef Singleton<ResourceManagerClass> ResourceManager;
}

#endif
