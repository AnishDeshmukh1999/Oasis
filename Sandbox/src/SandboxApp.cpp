#include<Oasis.h>
#include"loguru.hpp"
#include"loguru.cpp"
class ExampleLayer : public Oasis::Layer {
public:
	ExampleLayer() : Layer("Example") {}
	void onUpdate() override {
		LOG_F(INFO,"ExampleLayer: Updated");
		int q = 10;
	}
	void onEvent(Oasis::Event& e) override {
		LOG_F(INFO,"%s", e.toString().c_str());
		int k = 10;
	}
};
class SandBox : public Oasis::Application {
public:
	SandBox() {
		pushLayer(new ExampleLayer());
	}
	~SandBox() {

	}

};
Oasis::Application* Oasis::CreateApplication() {
	return new SandBox();
}