#include "Graphics.h"
#include "ResourceManager.h"
#include "Game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
    Graphics graphics(&argc, argv, "Casino game");

    ResourceManager::getInstance().loadTexture("background.tga");
    ResourceManager::getInstance().loadTexture("stripe.tga");
    ResourceManager::getInstance().loadTexture("start.tga");
    ResourceManager::getInstance().loadTexture("stop.tga");
    ResourceManager::getInstance().loadTexture("debian.tga");
    ResourceManager::getInstance().loadTexture("vim.tga");
    ResourceManager::getInstance().loadTexture("gentoo.tga");

    Game::getInstance().run();
    return 0;
}
