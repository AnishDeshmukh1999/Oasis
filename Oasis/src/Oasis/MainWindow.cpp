#include "MainWindow.h"
#include"Events/KeyEvent.h"
#include"Events/ApplicationEvent.h"
#include"Events/MouseEvent.h"
#include"glad/glad.h"
#include<signal.h>
namespace Oasis {
	static bool s_GLFWInitialised = false;
	static void GLFWErrorCallback(int error_code, const char* description) {
		LOG_F(ERROR, "Error code %d: %s", error_code, description);
	}
	Window* Window::Create(const WindowProp& prop) {
		return new MainWindow(prop);
	}
	static void glfwError(int id, const char* description)
	{
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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialised = true;
		}
		m_window = glfwCreateWindow((int)prop.width, (int)prop.height, prop.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_ASSERT(status, "Failed to initialise Glad");
		glfwSetWindowUserPointer(m_window, &m_data);
		setVSync(true);

		// GLFW Callbacks

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);

		});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xpos, (float)ypos);
		});
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
