#include "Player.h"
#include "ResourceManager.h"
#include <cmath>

Player::Player()
{
	ResourceManager::getInstance().loadTexture("shark.png");
	texture = ResourceManager::getInstance().getTexture("shark.png");
	init();
	playerWidth = 180;
	playerHeight = 100;
}

Player::~Player()
{
}

void Player::init()
{
	position.x = Graphics::getScreenWidth() / 4;
	position.y = Graphics::getScreenHeight() / 2 - texture->GetHeight() / 2;
	reset();
}

void Player::update(int dt, int waterY)
{
	static int frameTimer = 0;
	static int frame = 0;
	frameTimer += dt;
	if (frameTimer > 300)
	{
		frameTimer = 0;
		frame++;
		if (frame >= 3)
			frame = 0;
	}

	int posLimit = Graphics::getScreenHeight() / 2 - waterY;

	static int dposition = Graphics::getScreenHeight() / 100;
	static int animTimer = 0;
	animTimer += dt;
	if (animTimer > 100)
	{
		switch (state)
		{
		case Normal:
			position.y += dposition;
			if ((dposition > 0 && position.y > Graphics::getScreenHeight() / 2 + posLimit) ||
				(dposition < 0 && position.y < Graphics::getScreenHeight() / 2 - posLimit))
				dposition = -dposition;
			break;
		case Rising:
			position.y -= abs(dposition);
			if (position.y < waterY && riseAcceleration > 8)
				state = Jumping;
			else if (position.y <= waterY)
			{
				position.y += abs(dposition);
				riseAcceleration = 0;
			}
			break;
		case Falling:
			position.y += abs(dposition);
			break;
		case Jumping:
			{
				static int step = 0;
				static int k = 2;
				if (step == 20)
				{
					angle = M_PI/4;
					dposition = -dposition;
					//k *= 2;
				} else {
					if (step < 20)
						dposition = dposition > 0 ? -dposition : dposition;
				}
				position.y += dposition * k;
				step++;

				if (step == 50)
				{
					state = Normal;
					step = 0;
					k = 2;
					reset();
				}
			}
			break;
		}
	}

	Graphics::drawFrame(texture, position, playerWidth, playerHeight, -100, angle, frame, 3);
}

void Player::goUpper()
{
	if (state == Jumping)
		return;
	angle = -M_PI/4;
	state = Rising;
	riseAcceleration++;
	s3eDebugTracePrintf("%d", riseAcceleration);
}

void Player::goDowner()
{
	if (state == Jumping)
		return;
	angle = M_PI/4;
	state = Falling;
}

void Player::reset()
{
	if (state == Jumping)
		return;
	angle = 0.0f;
	state = Normal;
	riseAcceleration = 0;
}