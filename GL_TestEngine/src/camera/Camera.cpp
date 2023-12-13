#include "Camera.h"

#include <iostream>

namespace camera {
	Camera::Camera(unsigned int width, unsigned int height) {
		m_screenWidth = width;
		m_screenHeight = height;
	}

	void Camera::ViewMatrix(float FOV, float nearPlane, float farPlane, core::Shader& shader, const char* uniform) {
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_position, m_position + m_orientation, m_worldspaceUp);
		projection = glm::perspective(glm::radians(FOV), (float)(m_screenWidth / m_screenHeight), nearPlane, farPlane);

		glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
	}

	void Camera::HandleInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_position += m_speed * m_orientation;
		}
	}
}