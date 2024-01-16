#include "Camera.h"

#include "time/Time.h"

#include <iostream>

namespace engine {
	// TODO: Fix Screen width and height not being updated when Window is resized
	Camera::Camera(float FOV, float nearPlane, float farPlane, glm::vec3 position, int screenWidth, int screenHeight, Shader& shader) {
		m_fov = FOV;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;
		m_position = position;
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		m_shader = &shader;
	}

	void Camera::CalculateMVP() {
		m_shader->bind();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_position, m_position + m_orientation, m_up);
		projection = glm::perspective(glm::radians(m_fov), (float)(m_screenWidth / m_screenHeight), m_nearPlane, m_farPlane);

		m_shader->setUniformMat4("u_CameraMatrix", projection * view);
		m_shader->unbind();
	}

	void Camera::HandleInput(GLFWwindow& window, float sensitivity) {
		if (glfwGetKey(&window, GLFW_KEY_W)) {
			m_position -= sensitivity * m_front * Time::getDeltaTime();
		}
		if (glfwGetKey(&window, GLFW_KEY_S)) {
			m_position += sensitivity * m_front * Time::getDeltaTime();
		}
		if (glfwGetKey(&window, GLFW_KEY_D)) {
			m_position -= glm::normalize(glm::cross(m_front, m_up)) * sensitivity * Time::getDeltaTime();
		}
		if (glfwGetKey(&window, GLFW_KEY_A)) {
			m_position += glm::normalize(glm::cross(m_front, m_up)) * sensitivity * Time::getDeltaTime();
		}
	}
}