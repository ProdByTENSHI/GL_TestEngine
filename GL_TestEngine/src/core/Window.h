#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace core {
	class Window {
	public:
		Window();
		~Window();

		GLFWwindow* getWindow();
		const int getWidth();
		const int getHeight();

	private:
		GLFWwindow* m_window = nullptr;

		const char* m_TITLE = "OpenGL Test Engine";
		const int m_INIT_WIDTH = 1280;
		const int m_INIT_HEIGHT = 720;
	};
}