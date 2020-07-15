#pragma once
#include"Core.h"
#include"Events/Event.h"
namespace Oasis {
	struct WindowProp {
		std::string title;
		unsigned int width, height;
		WindowProp(std::string t = "Oasis Engine", unsigned int w = 1920, unsigned int h = 1080)
			:title(t), width(w), height(h) {}
	};
	class OE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual void onUpdate() = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallbackFn(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* Create(const WindowProp& windowprop = WindowProp());
	};
}