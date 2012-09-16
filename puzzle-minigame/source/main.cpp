#include "GameSDK/Graphics.h"
#include "GameSDK/Misc.h"
#include "GameSDK/Input.h"
#include "GameSDK/ResourceManager.h"
#include "Game.h"

using namespace GameSDK;

// locking to 30 fps
const int MS_PER_FRAME = 1000 / 30;

int main(int argc, char * argv[])
{
	Graphics::Init();

	Input input;
	Game game;
	game.Initialize();

	bool running;

	do {
		running = Misc::IsAppRunning();

		int64 timeStart = Misc::GetTimerMs();

		input.Update();
		if (input.Clicked())
			game.Click(input.GetMouseX(), input.GetMouseY());

		game.UpdateEffects();
		game.Render();

		while ((Misc::GetTimerMs() - timeStart) < MS_PER_FRAME)
		{
			int pause = (int)(MS_PER_FRAME - (Misc::GetTimerMs() - timeStart));
			if (pause < 0)
				break;
			Misc::Sleep(pause);
		}
	} while (running);

	ResourceManager::GetInstance().DestroyTextures();
	Graphics::Destroy();
}
