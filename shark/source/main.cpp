#include "Graphics.h"
#include "Input.h"
#include "Game.h"
#include "ResourceManager.h"
#include <s3e.h>

const int MS_PER_FRAME = 1000 / 40;

int main(int argc, char * argv[])
{
	std::srand((int)(s3eTimerGetMs() / 1000));
	Graphics::init();
	Input input;

	ResourceManager::getInstance().loadTexture("shark.png");

	Game game;
	game.init();

	int dt = 0;
	bool running;
	do {
		int64 timeStart = s3eTimerGetMs();
		running = s3eDeviceCheckQuitRequest() == S3E_FALSE;
		Graphics::prepareFrame();
		input.update();

		if (input.pressed())
			game.touch(input.getPointerX(), input.getPointerY());
		else if (input.clicked())
			game.release(input.getPointerX(), input.getPointerY());
		game.update(dt);

		Graphics::redraw();

		dt = s3eTimerGetMs() - timeStart;
		while (dt < MS_PER_FRAME)
		{
			int pause = (int)(MS_PER_FRAME - (s3eTimerGetMs() - timeStart));
			if (pause < 0)
				break;
			s3eDeviceYield(pause);
		}

		dt = s3eTimerGetMs() - timeStart;
	} while (running);

	ResourceManager::getInstance().destoryTextures();
	Graphics::destroy();
}