#include <map>
#include <string>
#include <IwTexture.h>

class ResourceManager
{
	std::map<std::string, CIwTexture*> textures;

public:
	ResourceManager();
	virtual ~ResourceManager();
	static ResourceManager& getInstance();
	void loadTexture(const char* textureName);
	CIwTexture* getTexture(const char* textureName);
	void destoryTextures();
};