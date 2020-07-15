#include<Oasis.h>
#include"spdlog/fmt/bundled/core.h"
class SandBox : public Oasis::Application {
public:
	SandBox() {

	}
	~SandBox() {

	}

};
Oasis::Application* Oasis::CreateApplication() {
	return new SandBox();
}