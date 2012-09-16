#include "YouWonEffect.h"
#include "GameSDK/ResourceManager.h"
#include "GameSDK/Misc.h"
#include "GameSDK/Graphics.h"

using namespace GameSDK;

YouWonEffect::YouWonEffect()
{
	// this framework has a kinda strange way of fonts using,
	// that's why I'll just use a picture with a text
	const Texture* youWonTexture = ResourceManager::GetInstance().GetTexture(3);
	float textureWidth = youWonTexture->GetWidth();
	float textureHeight = youWonTexture->GetHeight();

	for (int i = 1; i <	LETTERS_NUMBER + 1; ++i)
	{
		youWonTextureCoords[i - 1].left = LETTER_OFFSETS[i - 1];
		youWonTextureCoords[i - 1].top = 0.0f;
		youWonTextureCoords[i - 1].right = LETTER_OFFSETS[i];
		youWonTextureCoords[i - 1].bottom = textureHeight;
	}

	xOffset = (Misc::GetScreenWidth() - textureWidth) / 2;
	yOffset = (Misc::GetScreenHeight() - textureHeight) / 3;

	Reset();
}

YouWonEffect::~YouWonEffect()
{
}

void YouWonEffect::Render() const
{
	if (animStatus == Stopped)
		return;

	Rect screenCoords;
	for (int i = 0; i < LETTERS_NUMBER; ++i)
	{
		if (lettersDelta[i] == 0.0f)
			continue;

		screenCoords = youWonTextureCoords[i];

		float width = screenCoords.right - screenCoords.left;
		float height = screenCoords.bottom - screenCoords.top;

		screenCoords.left += (lettersDelta[i] * width) / 100.0f;
		screenCoords.top += (lettersDelta[i] * height) / 100.0f;
		screenCoords.right -= (lettersDelta[i] * width) / 100.0f;
		screenCoords.bottom -= (lettersDelta[i] * height) / 100.0f;

		Graphics::DrawTexture(screenCoords, 3, youWonTextureCoords[i], xOffset, yOffset);
	}
}

void YouWonEffect::Update()
{
	if (animStatus == Stopped || animStatus == Done)
		return;

	bool done = false;
	for (int i = 0; i < LETTERS_NUMBER; ++i)
	{
		if (i > 0)
		{
			if (lettersDelta[i] == lettersDelta[i - 1])
				continue;
			else
				done = true;
		}
		
		lettersDelta[i] -= STEP;
		if (lettersDelta[i] <= 0.0f)
			lettersDelta[i] = 1.0f;

		if (done)
			break;
	}

	if (lettersDelta[LETTERS_NUMBER - 1] <= 1.0f)
		animStatus = Done;
}

void YouWonEffect::Start()
{
	animStatus = Started;
}

void YouWonEffect::Reset()
{
	animStatus = Stopped;
	for (int i = 0; i < LETTERS_NUMBER; ++i)
		lettersDelta[i] = 50.0f;
}
