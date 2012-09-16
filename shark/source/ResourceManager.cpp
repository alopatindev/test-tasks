#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::loadTexture(const char* textureName)
{
	textures[textureName] = new CIwTexture;
	textures[textureName]->LoadFromFile((std::string("textures/") + std::string(textureName)).c_str());
	textures[textureName]->Upload();
}

CIwTexture* ResourceManager::getTexture(const char* textureName)
{
	return textures[textureName];
}

void ResourceManager::destoryTextures()
{
	for (std::map<std::string, CIwTexture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		delete it->second;
}