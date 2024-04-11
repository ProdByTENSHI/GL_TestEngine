#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace engine {
	class Window {
	public:
		void create(const std::string& title, int width, int height);

		~Window();

		GLFWwindow* getWindow();
		inline int* getWidth() { glfwGetWindowSize(m_window, &m_width, &m_height); return &m_width; }
		inline int* getHeight() { glfwGetWindowSize(m_window, &m_width, &m_height); return &m_height; }

		inline float getFramerateCap() const { return m_FRAMERATECAP; }

	private:
		GLFWwindow* m_window = nullptr;

		const float m_FRAMERATECAP = 1.0f / 60.0f;

		std::string m_title;

		int m_width = 0;
		int m_height = 0;
	};
}