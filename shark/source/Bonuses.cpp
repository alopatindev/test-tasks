#include "Bonuses.h"
#include "ResourceManager.h"

Bonuses::Bonuses()
{
	ResourceManager::getInstance().loadTexture("star.png");
}

Bonuses::~Bonuses()
{
}

void Bonuses::init()
{
	collectedBonuses = 0;

	for (int i = 0; i < MAX_BONUSES; ++i)
	{
		bonuses[i].x = Graphics::getScreenWidth() / MAX_BONUSES + rand() % (Graphics::getScreenWidth() / 70);
		bonuses[i].x *= i;
		bonuses[i].y = Graphics::getScreenHeight() / 2 - Graphics::getScreenHeight() / 4 + rand() % (Graphics::getScreenHeight() / 2);
		bonusesVisible[i] = true;
	}
	bonusesVisible[0] = false;
}

void Bonuses::update(int dt, const Point& playerPos, int playerWidth, int playerHeight)
{
	static int timer = 0;
	timer += dt;
	CIwTexture* texture = ResourceManager::getInstance().getTexture("star.png");

	if (timer > 50)
	{
		for (int i = 0; i < MAX_BONUSES; ++i)
		{
			bonuses[i].x -= 20;
			if (bonuses[i].x < -(int)texture->GetWidth())
			{
				bonuses[i].x = Graphics::getScreenWidth() / MAX_BONUSES + rand() % (Graphics::getScreenWidth() / 70);
				bonuses[i].x *= MAX_BONUSES;
				bonuses[i].y = Graphics::getScreenHeight() / 2 - Graphics::getScreenHeight() / 3 + rand() % (Graphics::getScreenHeight() / 3);
				bonusesVisible[i] = true;
			}

			int eps = 100;
			int bonusWidth = texture->GetWidth();
			if (bonusesVisible[i]&&
				bonuses[i].x >= playerPos.x - bonusWidth - eps &&
				bonuses[i].x <= playerPos.x + bonusWidth - eps &&
				bonuses[i].y >= playerPos.y - bonusWidth &&
				bonuses[i].x <= playerPos.x + bonusWidth)
			{
				collectedBonuses++;
				bonusesVisible[i] = false;
			}
		}
	}

	for (int i = 0; i < MAX_BONUSES; ++i)
	{
		if (bonusesVisible[i])
			Graphics::drawTexture(texture, bonuses[i].x, bonuses[i].y);
	}
}