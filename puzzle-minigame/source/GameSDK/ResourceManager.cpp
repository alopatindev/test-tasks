#include "ResourceManager.h"

using namespace GameSDK;

ResourceManagerClass::ResourceManagerClass()
{
}

ResourceManagerClass::~ResourceManagerClass()
{
	DestroyTextures();
}

void ResourceManagerClass::AddTexture(const char * filename)
{
	textures.push_back(TexturePair(filename, 0));
}

void ResourceManagerClass::LoadTextures()
{
	for (std::vector< TexturePair >::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		CIwTexture* texture = new CIwTexture;
		texture->LoadFromFile(it->first.c_str());
		texture->Upload();
		it->second = new Texture;
		it->second->SetData((void*)texture);
	}
}

void ResourceManagerClass::DestroyTextures()
{
	for (std::vector< TexturePair >::iterator it = textures.begin(); it != textures.end(); ++it)
		delete it->second;
	textures.clear();
}

Texture* ResourceManagerClass::GetTexture(int id) const
{
	return (size_t)id >= textures.size() || id < 0 ? 0 : textures[id].second;
}
