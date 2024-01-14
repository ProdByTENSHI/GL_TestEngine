#include "Camera.h"

#include <iostream>

namespace engine {
	Camera::Camera(float FOV, float nearPlane, float farPlane, glm::vec3 position, const int& screenWidth, const int& screenHeight, Shader& shader) {
		m_fov = FOV;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
		m_position = position;
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		m_shader = &shader;
	}

	void Camera::CalculateMVP(const char* uniform) {
		m_shader->bind();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_position, m_position + m_orientation, m_up);
		projection = glm::perspective(glm::radians(m_fov), (float)(m_screenWidth / m_screenHeight), m_nearPlane, m_farPlane);

		m_shader->setUniformMat4("u_CameraMatrix", projection * view);
		m_shader->unbind();
	}
}