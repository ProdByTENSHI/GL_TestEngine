#pragma once

#include "BaseComponent.h"
#include "UpdateComponent.h"

#include "renderer/Shader.h"

#include <glm/glm.hpp>

namespace engine {
	class TransformComponent : public BaseComponent, public UpdateComponent {
	public:
		TransformComponent(glm::vec3 position) { this->position = position; }

		glm::vec3 position;

		// Update the Position Uniform of the Object in the Shader
		void update(Shader& shader, const char* uniform) override {
			shader.bind();
			shader.setUniform3f(uniform, position.x, position.y, position.z);
			shader.unbind();
		}

		inline const ComponentType getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		ComponentType m_type = ComponentType::TransformType;

		const std::string m_name = "Transform Component";
		const bool m_isUnique = true;
	};
}