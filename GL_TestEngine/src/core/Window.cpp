#include "core/Window.h"

#include <iostream>

namespace engine {
	// TODO: Update Width and Height
	void onResize(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::create(const std::string& title, int width, int height) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (m_window == nullptr) {
			std::cout << "Could not create Window. Error: " << glfwGetError(NULL) << std::endl;
			return;
		}

		m_title = title;
		m_width = width;
		m_height = height;

		glfwMakeContextCurrent(m_window);

		glDisable(GL_FRAMEBUFFER_SRGB);
		glfwSetFramebufferSizeCallback(m_window, onResize);
		glfwSwapInterval(1);
		glViewport(0, 0, width, height);
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
	}

	GLFWwindow* Window::getWindow() {
		return m_window;
	}
}