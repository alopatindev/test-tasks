#ifndef GAMESDK_MISC_H
#define GAMESDK_MISC_H

#include <s3e.h>
#include <IwGx.h>

using namespace std;

namespace GameSDK
{
	class Misc
	{
	public:
		static int64 GetTimerMs()
		{
			return s3eTimerGetMs();
		}

		static void Sleep(int time)
		{
			s3eDeviceYield(time);
		}

		static bool IsAppRunning()
		{
			return s3eDeviceCheckQuitRequest() == S3E_FALSE;
		}

		static float GetScreenWidth()
		{
			return (float)IwGxGetDisplayWidth();
		}

		static float GetScreenHeight()
		{
			return (float)IwGxGetDisplayHeight();
		}

		static uint GetTimestamp()
		{
			return (uint)(s3eTimerGetUTC() / 1000);
		}
	};
}

#endif
