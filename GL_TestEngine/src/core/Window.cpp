#include "core/Window.h"

#include <iostream>

namespace engine {
	void onResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	Window::Window() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		m_window = glfwCreateWindow(m_INIT_WIDTH, m_INIT_HEIGHT, m_TITLE, NULL, NULL);
		if (m_window == nullptr) {
			std::cout << "Could not create Window. Error: " << glfwGetError(NULL) << std::endl;
			return;
		}

		m_width = m_INIT_WIDTH;
		m_height = m_INIT_HEIGHT;


		glfwMakeContextCurrent(m_window);

		glDisable(GL_FRAMEBUFFER_SRGB);
		glfwSetFramebufferSizeCallback(m_window, onResize);
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