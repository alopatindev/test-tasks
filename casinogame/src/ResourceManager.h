#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Singleton.h"
#include <map>
#include <string>
#include <GL/glut.h>

extern "C"
{
    #include "thirdparty/tgaload.h"
};

struct Texture
{
    GLuint id;
    int width;
    int height;
    int depth;
};

class ResourceManagerClass
{
    std::map<std::string, Texture> textures;

public:
    ResourceManagerClass();
    virtual ~ResourceManagerClass();
    
    void loadTexture(const char* textureName);
    const Texture* getTexture(const char* textureName);

    void freeTextures();
};

typedef Singleton<ResourceManagerClass> ResourceManager;

#endif
