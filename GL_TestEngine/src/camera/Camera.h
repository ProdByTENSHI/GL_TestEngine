#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "core/Shader.h"

namespace camera {
	class Camera {
	public:
		Camera(unsigned int screenWidth, unsigned int screenHeight);

		void ViewMatrix(float FOV, float nearPlane, float farPlane, core::Shader& shader, const char* uniform);
		void HandleInput(GLFWwindow* window);

	private:
		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 2.0f);
		glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_worldspaceUp = glm::vec3(0.0f, 1.0f, 0.0f);

		unsigned int m_screenWidth = 0;
		unsigned int m_screenHeight = 0;

		float m_speed = 0.1f;
		float m_sensitivity = 100.0f;
	};
}