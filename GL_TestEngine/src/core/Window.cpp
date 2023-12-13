#include "core/Window.h"

#include <iostream>

namespace core {
	Window::Window() {
		m_window = glfwCreateWindow(m_INIT_WIDTH, m_INIT_HEIGHT, m_TITLE, NULL, NULL);
		if (m_window == nullptr) {
			std::cout << "Could not create Window. Error: " << glfwGetError(NULL) << std::endl;
			return;
		}

		// Set Window Hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		glfwMakeContextCurrent(m_window);

		// Limit Framerate to Monitor Hertz
		glfwSwapInterval(1);

		glViewport(0, 0, m_INIT_WIDTH, m_INIT_HEIGHT);
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
	}

	GLFWwindow* Window::getWindow() {
		return m_window;
	}

	const int Window::getWidth() {
		int width;
		glfwGetWindowSize(m_window, &width, NULL);
		return width;
	}

	const int Window::getHeight() {
		int height;
		glfwGetWindowSize(m_window, NULL, &height);
		return m_INIT_HEIGHT;
	}
}