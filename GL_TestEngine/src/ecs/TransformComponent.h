#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BaseComponent.h"
#include "UpdateComponent.h"

#include "renderer/Shader.h"

namespace engine {
	class TransformComponent : public BaseComponent, public UpdateComponent {
	public:
		TransformComponent(glm::vec3 position, glm::fquat rotation, glm::vec3 scale) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;

			m_modelMatrix = glm::translate(m_modelMatrix, this->position);
			rotate(X_AXIS, rotation.x);
			rotate(Y_AXIS, rotation.y);
			rotate(Z_AXIS, rotation.z);
			m_modelMatrix = glm::scale(m_modelMatrix, scale);
		}

		void translate(glm::vec3 position) {
			m_modelMatrix = glm::translate(m_modelMatrix, position);
			this->position = position;
		}

		void rotate(glm::vec3 axis, float angleInDegrees) {
			m_modelMatrix = glm::rotate(m_modelMatrix, angleInDegrees, axis);
		}

		// Update the Transform Matrix Uniform of the Object in the Shader
		void update(Shader& shader) override {
			shader.setUniformMat4("u_ObjectTransform", m_modelMatrix);
		}

		inline const ComponentType getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

		glm::vec3 position;
		glm::fquat rotation;
		glm::vec3 scale;

		const static inline glm::vec3 X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
		const static inline glm::vec3 Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
		const static inline glm::vec3 Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);

	protected:
		ComponentType m_type = ComponentType::TransformType;

		const std::string m_name = "Transform Component";
		const bool m_isUnique = true;

	private:
		glm::mat4 m_modelMatrix = glm::mat4(1.0f);
	};
}