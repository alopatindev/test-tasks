#ifndef BONUSES_H
#define BONUSES_H

#include "Graphics.h"

const int MAX_BONUSES = 3;  // on the screen

class Bonuses
{
	Point bonuses[MAX_BONUSES];
	bool bonusesVisible[MAX_BONUSES];
	int collectedBonuses;

public:
	Bonuses();
	~Bonuses();
	void init();
	void update(int dt, const Point& playerPos, int playerWidth, int playerHeight);
	int popCollectedBonuses()
	{
		int b = collectedBonuses;
		collectedBonuses = 0;
		return b;
	}
};

#endif