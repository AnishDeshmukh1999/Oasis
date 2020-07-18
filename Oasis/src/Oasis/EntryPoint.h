#pragma once
#include"spdlog/fmt/bundled/format.h"
#include"../oepch.h"
#include"loguru.hpp"
#ifdef OE_PLATFORM_WINDOWS

extern Oasis::Application* Oasis::CreateApplication();
int main(int argc, char** argv) {
	//Oasis::Log::Init();
	loguru::init(argc, argv);
	LOG_F(INFO, "Initializing Oasis!");
	auto app = Oasis::CreateApplication();
	app->Run();
	delete app;
}

#endif