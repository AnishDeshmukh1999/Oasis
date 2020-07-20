#pragma once
#include"loguru.hpp"
#include<csignal>
#ifdef OE_PLATFORM_WINDOWS
	#ifdef OE_BUILD_DLL
		#define OE_API _declspec(dllexport)
	#else
		#define OE_API _declspec(dllimport)
	#endif
#else
	#error Oasis only supports Windows!
#endif

#define OE_ASSERT(x,...) {if(!x) {LOG_F(FATAL,"Assertion Failed: %s",__VA_ARGS__); raise(SIGINT);}}
#define BIT(x) (1 << (x))