#ifndef _PLATFORM_H
#define _PLATFORM_H 1

#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX 2

#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__linux__)
	#define PLATFORM PLATFORM_LINUX
#else
	#error Your platform is not usable for now
#endif

#endif // _PLATFORM_H
