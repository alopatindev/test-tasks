#ifndef PLAYER_H
#define PLAYER_H

#include "Graphics.h"

class Player
{
	Point position;
	int riseAcceleration;
	float angle;
	CIwTexture* texture;
	enum {Normal, Rising, Falling, Jumping} state;
	int playerWidth;
	int playerHeight;

public:
	Player();
	~Player();
	void update(int dt, int waterY);
	void goUpper();
	void goDowner();
	void reset();
	void init();
	Point getPosition() const
	{
		return position;
	}

	int getWidth() const
	{
		return playerWidth;
	}
	int getHeight() const
	{
		return playerHeight;
	}
};

#endif