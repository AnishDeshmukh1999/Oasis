#pragma once

#ifdef OE_PLATFORM_WINDOWS

extern Oasis::Application* Oasis::CreateApplication();
int main(int argc, char** argv) {
	Oasis::Log::Init();
	OE_CORE_INFO("Initializing Oasis!");
	OE_CORE_FATAL("Welcome var={0}", 5);
	auto app = Oasis::CreateApplication();
	app->Run();
	delete app;
}

#endif