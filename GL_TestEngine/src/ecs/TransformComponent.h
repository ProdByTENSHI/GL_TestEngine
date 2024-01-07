#pragma once

#include "BaseComponent.h"

#include <glm/glm.hpp>

namespace ecs {
	class TransformComponent : public BaseComponent {
	public:
		TransformComponent(glm::vec3 position) { this->position = position; }

		glm::vec3 position;

		inline const ComponentType getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		ComponentType m_type = ComponentType::Transform;

		const std::string m_name = "Transform Component";
		const bool m_isUnique = true;
	};
}