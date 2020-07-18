#pragma once
#include "Window.h"
#include <GLFW\glfw3.h>
#include"loguru.hpp"
namespace Oasis {
	class MainWindow : public Window
	{
	public:
		MainWindow(const WindowProp& windowprop);
		virtual ~MainWindow();
		void onUpdate() override;
		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }
		inline void setEventCallbackFn(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }

		void setVSync(bool VSync) override;
		bool isVSync() const override;

	private:
		virtual void Init(const WindowProp& windowprop);
		virtual void shutdown();
		GLFWwindow* m_window;
		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_data;
	};
}

