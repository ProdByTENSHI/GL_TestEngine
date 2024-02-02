#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BaseComponent.h"
#include "UpdateComponent.h"

#include "renderer/Shader.h"
#include "math/Axis.h"

namespace engine {
	class TransformComponent : public BaseComponent, public UpdateComponent {
	public:
		TransformComponent(const std::string& transformMatUniform, glm::vec3 position, glm::fquat rotation, glm::vec3 scale) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;

			m_transformMatrix = glm::translate(m_transformMatrix, this->position);

			rotate(X_AXIS, rotation.x);
			rotate(Y_AXIS, rotation.y);
			rotate(Z_AXIS, rotation.z);

			m_transformMatrix = glm::scale(m_transformMatrix, scale);

			m_transformMatUniform = transformMatUniform;
		}

		void translate(const glm::vec3& position) {
			m_transformMatrix = glm::translate(m_transformMatrix, position);
			this->position = position;
		}

		void rotate(const glm::vec3& axis, float angleInDegrees) {
			m_transformMatrix = glm::rotate(m_transformMatrix, angleInDegrees, axis);
		}

		// Update the Transform Matrix Uniform of the Object in the Shader
		void update(Shader& shader) override {
			shader.setUniformMat4(m_transformMatUniform, m_transformMatrix);
		}

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

		glm::vec3 position;
		glm::fquat rotation;
		glm::vec3 scale;

	protected:
		unsigned int m_type = ComponentType::UpdateType | ComponentType::TransformType;

		const std::string m_name = "Transform Component";
		const bool m_isUnique = true;

	private:
		std::string m_transformMatUniform;
		glm::mat4 m_transformMatrix = glm::mat4(1.0f);
	};
}