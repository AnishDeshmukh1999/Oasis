#include "MainWindow.h"
#include"Events/KeyEvent.h"
#include"Events/ApplicationEvent.h"
#include"Events/MouseEvent.h"
#include"glad/glad.h"
#include<signal.h>
#include"Application.h"
#include <iostream>
#include <fstream>
#include<string>
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


		//Shader stuff
		// Vertex Shader File Handling
		//std::string s, content;
		//std::fstream Vertexfile;
		//Vertexfile.open("C:\\dev\\Oasis\\Oasis\\src\\Oasis\\Shaders\\VertexShaderFile.glsl", std::ios::in);
		//if (Vertexfile.is_open()) {
		//	while (std::getline(Vertexfile, s))
		//	{
		//		content += s + '\n';
		//	}
		//}
		//else {
		//	LOG_F(ERROR, "Cannot Open Vertex Shader File");
		//}
		//const char* VertexShaderSource;
		//VertexShaderSource = content.c_str();
		//unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
		//glCompileShader(vertexShader);
		//// Fragment Shader File Handling
		//s = content = "";
		//std::fstream Fragmentfile;
		//Fragmentfile.open("C:\\dev\\Oasis\\Oasis\\src\\Oasis\\Shaders\\FragmentShaderFile.glsl", std::ios::in);
		//if (Fragmentfile.is_open()) {
		//	while (std::getline(Fragmentfile, s))
		//	{
		//		content += s + '\n';
		//	}
		//}
		//else {
		//	LOG_F(ERROR, "Cannot Open Fragment Shader File");
		//}
		//Fragmentfile.close();
		//const char* FragmentShaderSource;
		//FragmentShaderSource= content.c_str();
		//unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
		//glCompileShader(FragmentShader);
		////Attaching and linking shaders to the program
		//shaderProgram = glCreateProgram();
		//glAttachShader(shaderProgram, vertexShader);
		//glAttachShader(shaderProgram, FragmentShader);
		//glLinkProgram(shaderProgram);
		//glUseProgram(shaderProgram);
		////Deleting Shaders
		//glDeleteShader(vertexShader);
		//glDeleteShader(FragmentShader);
		//float vertices[] = {
		//	-0.5f, -0.5f, 0.0f,
		//	 0.5f, -0.5f, 0.0f,
		//	 0.0f,  0.5f, 0.0f
		//};
		//glGenVertexArrays(1, &VAO);
		//unsigned int VBO;
		//glGenBuffers(1, &VBO);
		//glBindVertexArray(VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
		//glEnableVertexAttribArray(0);

        

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
					if (key == GLFW_KEY_ESCAPE) {
						WindowCloseEvent event;
						glfwSetWindowShouldClose(window, true);
					}
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
		LOG_F(INFO, "Shutting down GLFW");
		glfwTerminate();
	}
	void MainWindow::onUpdate() {
		glClearColor(0.5, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		//glUseProgram(shaderProgram);
		//float timeValue = glfwGetTime();
		//float redValue = abs(sin(timeValue));
		//float greenValue = abs(cos(timeValue));
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "t");
		////glUniform4f(vertexColorLocation, redValue,greenValue, 0.0f, 1.0f);
		//glUniform1f(vertexColorLocation,timeValue);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(m_window);
		glfwPollEvents();
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
