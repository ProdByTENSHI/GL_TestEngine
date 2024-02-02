#include "Camera.h"

#include <iostream>

#include "Math/Easing.h"
#include "time/Time.h"

namespace engine {
	Camera::Camera(float FOV, float nearPlane, float farPlane, glm::vec3 position, const int& screenWidth, const int& screenHeight, Shader& shader) {
		m_fov = FOV;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
		m_position = position;
		m_screenWidth = &screenWidth;
		m_screenHeight = &screenHeight;

		m_shader = &shader;

		CalculateProjection();
	}

	void Camera::CalculateProjection() {
		m_shader->bind();
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(m_fov), (float)(*m_screenWidth / *m_screenHeight), m_nearPlane, m_farPlane);
		m_shader->setUniformMat4("u_CameraProjection", projection);
		m_shader->unbind();
	}

	void Camera::CalculateView() {
		m_shader->bind();
		glm::mat4 view = glm::mat4(1.0f);

		view = glm::lookAt(m_position, m_position + m_orientation, m_up);

		m_shader->setUniformMat4("u_CameraView", view);
		m_shader->unbind();
	}

	void Camera::HandleInput(GLFWwindow& window, float sensitivity) {
		if (glfwGetKey(&window, GLFW_KEY_W)) {
			m_position -= m_front * (sensitivity * Time::getDeltaTime());
		}
		if (glfwGetKey(&window, GLFW_KEY_S)) {
			m_position += m_front * (sensitivity * Time::getDeltaTime());
		}
		if (glfwGetKey(&window, GLFW_KEY_D)) {
			m_position -= glm::normalize(glm::cross(m_front, m_up)) * (sensitivity * Time::getDeltaTime());
		}
		if (glfwGetKey(&window, GLFW_KEY_A)) {
			m_position += glm::normalize(glm::cross(m_front, m_up)) * (sensitivity * Time::getDeltaTime());
		}
	}
}