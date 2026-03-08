#pragma once


#define MKSHOT_PLATFORM_WINDOWS 0
#define MKSHOT_PLATFORM_MACOS 1
#define MKSHOT_PLATFORM_LINUX 2

#ifdef _WIN32
#define MKSHOT_PLATFORM MKSHOT_PLATFORM_WINDOWS
#elif defined __APPLE__
#define MKSHOT_PLATFORM MKSHOT_PLATFORM_MACOS
#elif defined __linux__
#define MKSHOT_PLATFORM MKSHOT_PLATFORM_LINUX
#else
#error "Can't identify platform."
#endif

#include <string>

namespace systemImpl
{
	enum WineHostType
	{
		Windows,
		Linux,
		Mac
	};

	std::string getLanguage();
	std::string getUserName();
	std::string getUserFullName();

	int getScalingFactor();

	bool isWine();
	bool isRosetta();
	WineHostType getRealHostType();
}

#ifdef MKSHOT_BUILD_XCODE
std::string getPlistValue(const char *key);
void openSettingsWindow();
bool isMetalSupported();
#endif

namespace mkshot_sys = systemImpl;


