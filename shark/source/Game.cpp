#include "Game.h"
#include "Graphics.h"
#include "ResourceManager.h"
#include "IwGxPrint.h"
#include <cstdio>

Game::Game()
{
	ResourceManager::getInstance().loadTexture("water.png");
	ResourceManager::getInstance().loadTexture("restart_button.png");
	ResourceManager::getInstance().loadTexture("restart_window.png");

	CIwTexture* buttonTexture = ResourceManager::getInstance().getTexture("restart_button.png");
	restartButton.x = Graphics::getScreenWidth() / 2 - buttonTexture->GetWidth() / 2;
	restartButton.y = Graphics::getScreenHeight() / 2 + buttonTexture->GetHeight() / 4;
}

Game::~Game()
{
}

void Game::init()
{
	bonuses.init();
	player.init();
	score = 0;
	gameTimer = 0;
	pressedInGame = false;
}

void Game::update(int dt)
{
	gameTimer += dt;
	if (gameOver())
	{
		gameTimer = MAX_GAME_TIME * 1000;

		CIwTexture* windowTexture = ResourceManager::getInstance().getTexture("restart_window.png");
		CIwTexture* buttonTexture = ResourceManager::getInstance().getTexture("restart_button.png");
		Graphics::drawTexture(windowTexture, Graphics::getScreenWidth() / 2 - windowTexture->GetWidth() / 2,
							  Graphics::getScreenHeight() / 2 - windowTexture->GetHeight() / 2);
		Graphics::drawTexture(buttonTexture, restartButton.x, restartButton.y);

		char scoreText[128];
		std::sprintf(scoreText, "Score: %d", score);
		IwGxPrintString(Graphics::getScreenWidth() / 2 - (strnlen(scoreText, 128) * 7) / 2, Graphics::getScreenHeight() / 2 - 7/2, scoreText);
	} else {
		int waterY = Graphics::getScreenHeight() / 2 - Graphics::getScreenHeight() / 20;
		drawBackground(dt, waterY);
		player.update(dt, waterY);
		bonuses.update(dt, player.getPosition(), player.getWidth(), player.getHeight());
		score += bonuses.popCollectedBonuses() * 100;
		char scoreText[128];
		std::sprintf(scoreText, "Score: %d  Time: %d", score, MAX_GAME_TIME - gameTimer / 1000);
		IwGxPrintString(20, Graphics::getScreenHeight() - 20, scoreText);
	}
}

void Game::drawBackground(int dt, int waterY)
{
	static int dx = 0;
	static int timer = 0;
	timer += dt;

	CIwTexture* texture = ResourceManager::getInstance().getTexture("water.png");

	if (timer > 200)
	{
		timer = 0;
		dx -= texture->GetWidth() / 20;
		if (dx <= -(int)(texture->GetWidth()))
			dx = 0;
	}

	Point p[4];
	for (int i = 0; i < Graphics::getScreenWidth() / (int)texture->GetWidth() + 2; ++i)
	{
		int x = i * texture->GetWidth() + dx;
		p[0].x = x;
		p[0].y = waterY - texture->GetHeight() / 2;
		p[1].x = x;
		p[1].y = waterY + texture->GetHeight() / 2;
		p[2].x = x + texture->GetWidth();
		p[2].y = waterY - texture->GetHeight() / 2;
		p[3].x = x + texture->GetWidth();
		p[3].y = waterY + texture->GetHeight() / 2;

		Graphics::drawTexture(texture, p[0], p[1], p[2], p[3]);
	}

	p[0].x = 0; p[0].y = 0;
	p[1].x = 0;	p[1].y = waterY;
	p[2].x = Graphics::getScreenWidth(); p[2].y = 0;
	p[3].x = Graphics::getScreenWidth(); p[3].y = waterY;

	Point uv[4];
	uv[0].x = 0; uv[0].y = 0;
	uv[1].x = 0; uv[1].y = 1;
	uv[2].x = 1; uv[2].y = 0;
	uv[3].x = 1; uv[3].y = 1;

	// sky
	Graphics::drawTexture(texture, p[0], p[1], p[2], p[3], uv[0], uv[1], uv[2], uv[3]);

	p[0].x = 0; p[0].y = waterY + texture->GetHeight() / 2;
	p[1].x = 0; p[1].y = Graphics::getScreenHeight();
	p[2].x = Graphics::getScreenWidth(); p[2].y = waterY + texture->GetHeight() / 2;
	p[3].x = Graphics::getScreenWidth(); p[3].y = Graphics::getScreenHeight();

	uv[0].x = 0; uv[0].y = texture->GetHeight() - 1;
	uv[1].x = 0; uv[1].y = texture->GetHeight();
	uv[2].x = 1; uv[2].y = texture->GetHeight() - 1;
	uv[3].x = 1; uv[3].y = texture->GetHeight();

	// water gradient
	Graphics::drawTexture(texture, p[0], p[1], p[2], p[3], uv[0], uv[1], uv[2], uv[3]);
}

void Game::touch(int x, int y)
{
	if (!gameOver())
		pressedInGame = true;

	if (y < Graphics::getScreenHeight() / 2)
		player.goUpper();
	else
		player.goDowner();
}

void Game::release(int x, int y)
{
	if (gameOver())
	{
		CIwTexture* buttonTexture = ResourceManager::getInstance().getTexture("restart_button.png");
		if (!pressedInGame && x >= restartButton.x && y >= restartButton.y &&
			x <= restartButton.x + (int)buttonTexture->GetWidth() &&
			y <= restartButton.y + (int)buttonTexture->GetHeight())
		{
			init();
			s3eDeviceUnYield();
		}
	} else {
		player.reset();
	}
	pressedInGame = false;
}