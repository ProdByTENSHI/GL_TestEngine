#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {
	class Window {
	public:
		Window();
		~Window();

		GLFWwindow* getWindow();
		inline const int& getWidth() { glfwGetWindowSize(m_window, &m_width, &m_height); return m_width; }
		inline const int& getHeight() { glfwGetWindowSize(m_window, &m_width, &m_height); return m_height; }

	private:
		GLFWwindow* m_window = nullptr;

		const char* m_TITLE = "OpenGL Test Engine";
		const int m_INIT_WIDTH = 1280;
		const int m_INIT_HEIGHT = 720;

		int m_width = 0;
		int m_height = 0;
	};
}