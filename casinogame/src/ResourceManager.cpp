#include "ResourceManager.h"
#include <cstdlib>

ResourceManagerClass::ResourceManagerClass()
{
}

ResourceManagerClass::~ResourceManagerClass()
{
}

void ResourceManagerClass::loadTexture(const char* textureName)
{
    GLuint textureId;
    tga_data_t* tga = tga_data_load(
        ("textures/" + std::string(textureName)).c_str()
    );
    glGenTextures(1, &textureId);
    textures[textureName].id = textureId;
    textures[textureName].width = (int)tga->w;
    textures[textureName].height = (int)tga->h;
    textures[textureName].depth = (int)tga->depth;
    Texture* texture = &textures[textureName];

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 texture->depth <= 24 ? GL_RGB : GL_RGBA,
                 texture->width,
                 texture->height,
                 0,
                 texture->depth <= 24 ? GL_RGB : GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 tga->data);
    std::free(tga->data);
    std::free(tga);
}

const Texture* ResourceManagerClass::getTexture(const char* textureName)
{
    return &textures[textureName];
}

void ResourceManagerClass::freeTextures()
{
    for (std::map<std::string, Texture>::iterator it = textures.begin();
         it != textures.end();
         ++it)
    {
        glDeleteTextures(1, &it->second.id);
    }

    textures.clear();
}
