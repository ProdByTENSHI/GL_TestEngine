#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "renderer/Shader.h"

namespace engine {
	class Camera {
	public:
		Camera(float FOV, float nearPlane, float farPlane, glm::vec3 position, const int& screenWidth, const int& screenHeight, Shader& shader);
		void CalculateMVP(const char* uniform);

	private:
		float m_fov = 0.0f;
		float m_nearPlane = 0.0f;
		float m_farPlane = 0.0f;

		int m_screenWidth = 0;
		int m_screenHeight = 0;

		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

		Shader* m_shader;
	};
}