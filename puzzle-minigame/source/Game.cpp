#include "Game.h"
#include "GameSDK/Graphics.h"
#include "GameSDK/ResourceManager.h"
#include "GameSDK/Misc.h"

using namespace GameSDK;

Game::Game()
{
	ResourceManager::GetInstance().AddTexture("textures/pointer.png");
	ResourceManager::GetInstance().AddTexture("textures/novgorod.jpg");
	ResourceManager::GetInstance().AddTexture("textures/packman.jpg");
	ResourceManager::GetInstance().AddTexture("textures/youwon.png");
	ResourceManager::GetInstance().AddTexture("textures/restart.png");
	ResourceManager::GetInstance().LoadTextures();

	// restart button
	float restartWidth = Misc::GetScreenWidth() / 5;
	float restartHeight = Misc::GetScreenHeight() / 7;
	float screenWidth = Misc::GetScreenWidth();
	float screenHeight = Misc::GetScreenHeight();
	restartButtonScreenCoords.left = (screenWidth - restartWidth) / 2;
	restartButtonScreenCoords.top = (screenHeight - restartHeight) / 2 + screenHeight / 7;
	restartButtonScreenCoords.right = (screenWidth + restartWidth) / 2;
	restartButtonScreenCoords.bottom = (screenHeight + restartHeight) / 2 + screenHeight / 7;

	youWonEffect = new YouWonEffect;
}

Game::~Game()
{
	delete youWonEffect;
	ResourceManager::GetInstance().DestroyTextures();
}

void Game::Initialize()
{
	Texture* texture = ResourceManager::GetInstance().GetTexture(cTextureId);
	textureRectWidth = texture->GetWidth() / (float)cColumns;
	textureRectHeight = texture->GetHeight() / (float)cRows;
	screenRectWidth = Misc::GetScreenWidth() / (float)cColumns;
	screenRectHeight = Misc::GetScreenHeight() / (float)cRows;
	screenWidth = Misc::GetScreenWidth();
	screenHeight = Misc::GetScreenHeight();

	selected.i = -1;
	selected.j = -1;

	// game field randomizing
	std::srand((uint)(Misc::GetTimestamp()));
	do
	{
		std::memset(field, -1, sizeof(int) * cRows * cColumns);
		int k = 0;
		while (k < cRows * cColumns)
		{
			int i = rand() % cRows;
			int j = rand() % cColumns;
			while (field[i][j] != -1)
			{
				int nextPiece = GetPieceNumber(i, j) + 1;
				if (nextPiece >= cColumns * cRows)
				{
					i = 0;
					j = 0;
					continue;
				}
				Cell pieceIndex = GetPieceIndex(nextPiece);
				i = pieceIndex.i;
				j = pieceIndex.j;
			}

			field[i][j] = k;
			++k;
		}
	} while (CountMatches() >= (cRows * cColumns) / 2); // we don't need (almost) completed game at start

	// configuring effects/features
	swapping = false;
	youWonEffect->Reset();

	Texture* pointerTexture = ResourceManager::GetInstance().GetTexture(0);
	pointerRect.left = 0.0f;
	pointerRect.top = 0.0f;
	pointerRect.right = pointerTexture->GetWidth();
	pointerRect.bottom = pointerTexture->GetHeight();
}

void Game::Click(float x, float y)
{
	if (swapping || youWonEffect->getStatus() == YouWonEffect::Started)
		return;

	if (IsCompleted())
	{
		if (x >= restartButtonScreenCoords.left && x <= restartButtonScreenCoords.right &&
			y >= restartButtonScreenCoords.top && y <= restartButtonScreenCoords.bottom)
		{
			Initialize();
		}
		return;
	}

	Cell cell;
	cell.i = (int) ((y * (float)cRows) / screenHeight);
	cell.j = (int) ((x * (float)cColumns) / screenWidth);

	if (selected == cell)
		return;

	if (selected.i == -1)
	{
		selected.i = cell.i;
		selected.j = cell.j;
	} else {
		SwapCells(cell, selected);
	}
}

bool Game::IsCompleted() const
{
	int k = 0;
	for (int i = 0; i < cRows; ++i)
		for (int j = 0; j < cColumns; ++j)
		{
			if (field[i][j] != k)
				return false;
			k++;
		}
	return true;
}

void Game::Render() const
{
	Graphics::PrepareFrame();

	// game field
	Rect screenCoords, textureCoord;
	for (int i = 0; i < cRows; ++i)
		for (int j = 0; j < cColumns; ++j)
		{
			screenCoords.left = j * screenRectWidth;
			screenCoords.top = i * screenRectHeight;
			screenCoords.right = (j + 1) * screenRectWidth;
			screenCoords.bottom = (i + 1) * screenRectHeight;

			Rect pointerScreenCoords = screenCoords;

			// swapping effect
			Cell currentCell(i, j);
			if (swapping && (swappingCell[0] == currentCell ||
							 swappingCell[1] == currentCell))
			{
				screenCoords.left += (swappingDelta * screenRectWidth) / 100.0f;
				screenCoords.top += (swappingDelta * screenRectHeight) / 100.0f;
				screenCoords.right -= (swappingDelta * screenRectWidth) / 100.0f;
				screenCoords.bottom -= (swappingDelta * screenRectHeight) / 100.0f;
			}

			// getting cell index in the texture
			Cell index = GetPieceIndex(field[i][j]);

			textureCoord.left = index.j * textureRectWidth;
			textureCoord.top = index.i * textureRectHeight;
			textureCoord.right = (index.j + 1) * textureRectWidth;
			textureCoord.bottom = (index.i + 1) * textureRectHeight;
			
			DrawRect(screenCoords, cTextureId, textureCoord);

			// pointer
			if (!swapping && selected == currentCell)
				DrawRect(pointerScreenCoords, 0, pointerRect);
		}

	youWonEffect->Render();

	// restart button
	if (youWonEffect->getStatus() == YouWonEffect::Done)
	{
		Graphics::DrawTexture(restartButtonScreenCoords, 4);
	}

	Graphics::Redraw();
}

int Game::CountMatches() const
{
	int result = 0;
	int k = 0;
	for (int i = 0; i < cRows; ++i)
		for (int j = 0; j < cColumns; ++j)
		{
			if (field[i][j] == k)
				result++;
			k++;
		}
	return result;
}

void Game::SwapCells(Cell& cell0, Cell& cell1)
{
	swappingCell[0] = cell0;
	swappingCell[1] = cell1;
	swapping = true;
	swappingEnding = false;
	swappingDelta = 0.0f;
}

void Game::UpdateSwapping()
{
	if (!swapping)
		return;

	if (!swappingEnding)
		swappingDelta += 5.0f;
	else
		swappingDelta -= 5.0f;

	if (!swappingEnding && swappingDelta >= 50.0f)
	{
		int temp = field[swappingCell[0].i][swappingCell[0].j];
		field[swappingCell[0].i][swappingCell[0].j] = field[selected.i][selected.j];
		field[selected.i][selected.j] = temp;
		selected.i = -1;
		selected.j = -1;
		swappingDelta = 50.0f;
		swappingEnding = true;
	}

	if (swappingEnding && swappingDelta <= 0.0f)
	{
		swapping = false;
		if (IsCompleted())
			youWonEffect->Start();
	}
}

void Game::UpdateEffects()
{
	UpdateSwapping();
	youWonEffect->Update();
}

int Game::GetPieceNumber(int i, int j) const
{
	return (i + 1) * cColumns - (cColumns - j);
}

Cell Game::GetPieceIndex(int pieceNumber) const
{
	Cell result;
	result.i = pieceNumber / cColumns;
	result.j = pieceNumber - cColumns * result.i;
	return result;
}

void DrawRect(const Rect& screenCoords, int textureId, const Rect& textureCoord)
{
	Graphics::DrawTexture(screenCoords, textureId, textureCoord);
}
