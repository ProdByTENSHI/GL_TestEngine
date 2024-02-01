#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <GLFW/glfw3.h>

#include "renderer/Shader.h"

namespace engine {
	class Camera {
	public:
		Camera(float FOV, float nearPlane, float farPlane, glm::vec3 position, const int& screenWidth, const int& screenHeight, Shader& shader);

		// Only do this on Start Up and when the Window is resized
		void CalculateProjection();

		// The View has to be calculated every Frame
		void CalculateView();
		void HandleInput(GLFWwindow& window, float sensitivity);

		const inline glm::vec3 getPosition() { return m_position; }

	private:
		float m_fov = 0.0f;
		float m_nearPlane = 0.0f;
		float m_farPlane = 0.0f;

		const int* m_screenWidth = nullptr;
		const int* m_screenHeight = nullptr;

		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_front = glm::vec3(0.0f, 0.0f, 1.0f);

		Shader* m_shader;
	};
}