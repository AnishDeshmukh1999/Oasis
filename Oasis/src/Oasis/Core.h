#pragma once
#ifdef OE_PLATFORM_WINDOWS
	#ifdef OE_BUILD_DLL
		#define OE_API _declspec(dllexport)
	#else
		#define OE_API _declspec(dllimport)
	#endif
#else
	#error Oasis only supports Windows!
#endif

#define BIT(x) (1 << (x))