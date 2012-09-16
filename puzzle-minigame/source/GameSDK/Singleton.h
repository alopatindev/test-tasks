#ifndef GAMESDK_SINGLETON
#define GAMESDK_SINGLETON

namespace GameSDK {
	template <typename T>
	class Singleton
	{
	public:
		static T & GetInstance()
		{
			static T instance;
			return instance;
		}

	private:
		void operator=(Singleton const &) {}
	};
}

#endif
