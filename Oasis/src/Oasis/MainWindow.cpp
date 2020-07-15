#include "../oepch.h"
#include "MainWindow.h"
#include "Log.h"
#include"GLFW/glfw3.h"
namespace Oasis {
	static bool s_GLFWInitialised = false;
	Window* Window::Create(const WindowProp& prop) {
		return new MainWindow(prop);
	}
	static void glfwError(int id, const char* description)
	{
		OE_CORE_ERROR(description);
	}
	MainWindow::MainWindow(const WindowProp& prop) {
		int x = 5;
		glfwSetErrorCallback(&glfwError);
		Init(prop);
	}
	MainWindow::~MainWindow() { shutdown(); }

	void MainWindow::Init(const WindowProp& prop) {
		m_data.height = prop.height;
		m_data.width = prop.width;
		m_data.title = prop.title;

		if (!s_GLFWInitialised) {
			int success = glfwInit();
			s_GLFWInitialised = true;
		}
		m_window = glfwCreateWindow((int)prop.width, (int)prop.height, prop.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);
	}
	void MainWindow::shutdown() {
		glfwDestroyWindow(m_window);
	}
	void MainWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
	void MainWindow::setVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_data.VSync = enabled;
	}
	bool MainWindow::isVSync() const {
		return m_data.VSync;
	}
}
