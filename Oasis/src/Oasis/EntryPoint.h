#pragma once

#ifdef OE_PLATFORM_WINDOWS

extern Oasis::Application* Oasis::CreateApplication();
int main(int argc, char** argv) {
	auto app = Oasis::CreateApplication();
	app->Run();
	delete app;
}

#endif