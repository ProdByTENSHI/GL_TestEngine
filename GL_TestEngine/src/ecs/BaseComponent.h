#pragma once

#include <string>
#include <iostream>

#include "renderer/Shader.h"
#include "utility/Bit.h"

namespace engine {
	enum ComponentType {
		InvalidComponent = BIT(0),
		UpdateType = BIT(1),
		RenderType = BIT(2),
		LightType = BIT(3),

		TransformType = BIT(4),
		ModelType = BIT(5),	TextureType = BIT(6),
		AmbientLightType = BIT(7), DirectionalLightType = BIT(8)
	};

	class BaseComponent {
	public:
		friend bool operator==(const BaseComponent& lhs, const BaseComponent& rhs) { return lhs.m_type == rhs.m_type; }
		friend bool operator!=(const BaseComponent& lhs, const BaseComponent& rhs) { return !(lhs.m_type == rhs.m_type); }
		friend std::ostream& operator<<(std::ostream& os, const BaseComponent& component) { os << component.m_name << " : " << component.m_type; return os; }

		virtual inline const unsigned int getType() { return m_type; }
		virtual inline const std::string& getName() { return m_name; }
		virtual inline const bool isComponentUnique() { return m_isUnique; }

		virtual void setShaderUniforms(Shader& shader) { }

		virtual void onAdd() { }		// Gets called when the Component is added to an Entity
		virtual void onRemove() { }		// Gets called when the Component is removed from an Entity

	protected:
		unsigned int m_type = ComponentType::InvalidComponent;

		const std::string m_name = "Undefined";
		const bool m_isUnique = true;				// If this is true the Component cannot be added twice to an Entity
	};
}