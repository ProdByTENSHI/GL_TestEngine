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
	class TransformComponent : public BaseComponent {
	public:
		TransformComponent(glm::vec3 position, glm::fquat rotation, glm::vec3 scale) {
			this->m_position = position;
			this->m_rotation = rotation;
			this->m_scale = scale;

			m_transformMatrix = glm::translate(m_transformMatrix, this->m_position);

			rotate(X_AXIS, rotation.x);
			rotate(Y_AXIS, rotation.y);
			rotate(Z_AXIS, rotation.z);

			m_transformMatrix = glm::scale(m_transformMatrix, scale);
		}

		void translate(const glm::vec3& position) {
			m_transformMatrix = glm::translate(m_transformMatrix, position);
			this->m_position = position;
		}

		void rotate(const glm::vec3& axis, float angleInDegrees) {
			m_transformMatrix = glm::rotate(m_transformMatrix, angleInDegrees, axis);
			this->m_rotation = axis * angleInDegrees;
		}

		// TOOD: Implement Scaling

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

		inline const glm::vec3& getPosition() {
			return m_position;
		}

		inline const glm::fquat& getRotation() {
			return m_rotation;
		}

		inline const glm::vec3 getScale() {
			return m_scale;
		}

		inline const glm::mat4& getTransformationMatrix() {
			return m_transformMatrix;
		}

	protected:
		unsigned int m_type = ComponentType::TransformType;

		const std::string m_name = "Transform Component";
		const bool m_isUnique = true;

	private:
		glm::vec3 m_position;
		glm::fquat m_rotation;
		glm::vec3 m_scale;

		glm::mat4 m_transformMatrix = glm::mat4(1.0f);
	};
}