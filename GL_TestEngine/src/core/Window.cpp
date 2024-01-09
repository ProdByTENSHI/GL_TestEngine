#include "core/Window.h"

#include <iostream>

namespace core {
	Window::Window() {
		m_window = glfwCreateWindow(m_INIT_WIDTH, m_INIT_HEIGHT, m_TITLE, NULL, NULL);
		if (m_window == nullptr) {
			std::cout << "Could not create Window. Error: " << glfwGetError(NULL) << std::endl;
			return;
		}

		m_width = m_INIT_WIDTH;
		m_height = m_INIT_HEIGHT;

		// Set Window Hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		glfwMakeContextCurrent(m_window);

		glDisable(GL_FRAMEBUFFER_SRGB);

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
}