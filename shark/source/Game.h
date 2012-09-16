#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Bonuses.h"
#include "Graphics.h"

const int MAX_GAME_TIME = 60;

class Game
{
	Player player;
	Bonuses bonuses;
	int score;
	int gameTimer;
	bool pressedInGame;
	Point restartButton;

public:
	Game();
	virtual ~Game();
	void init();

	void update(int dt);
	void drawBackground(int dt, int waterY);
	void touch(int x, int y);
	void release(int x, int y);

	bool gameOver() const
	{
		return gameTimer >= MAX_GAME_TIME * 1000;
	}
};

#endif