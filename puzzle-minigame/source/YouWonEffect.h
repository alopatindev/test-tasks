#ifndef YOUWONEFFECT_H
#define YOUWONEFFECT_H

#include "Game.h"

static const int LETTERS_NUMBER = 7;
static float LETTER_OFFSETS[LETTERS_NUMBER + 1] = {0.0f, 106.0f, 193.0f, 303.0f, 496.0f, 590.0f, 705.0f, 750.0f};
static const float STEP = 7.0f;

class YouWonEffect
{
public:
	typedef enum {Stopped, Started, Done} Status;

private:
	Status animStatus;
	Rect youWonTextureCoords[LETTERS_NUMBER];
	float lettersDelta[LETTERS_NUMBER];
	float xOffset;
	float yOffset;

public:
	YouWonEffect();
	~YouWonEffect();
	void Render() const;
	void Update();
	void Start();
	void Reset();
	Status getStatus() const
	{
		return animStatus;
	}
};

#endif