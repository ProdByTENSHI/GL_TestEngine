#pragma once

#include <string>
#include <iostream>

namespace ecs {
	enum ComponentType {
		None = 1 << 0,
		Transform = 1 << 1,
		Mesh = 1 << 2
	};

	class BaseComponent {
	public:
		friend bool operator==(const BaseComponent& lhs, const BaseComponent& rhs) { return lhs.m_type == rhs.m_type; }
		friend bool operator!=(const BaseComponent& lhs, const BaseComponent& rhs) { return !(lhs.m_type == rhs.m_type); }
		friend std::ostream& operator<<(std::ostream& os, const BaseComponent& component) { os << component.m_name << " : " << component.m_type; return os; }

		virtual inline const ComponentType getType() { return m_type; }
		virtual inline const std::string& getName() { return m_name; }
		virtual inline const bool isComponentUnique() { return m_isUnique; }

	protected:
		ComponentType m_type = ComponentType::None;

		const std::string m_name = "Undefined";
		const bool m_isUnique = true;				// If this is True the Component cannot be added twice to an Entity
	};
}