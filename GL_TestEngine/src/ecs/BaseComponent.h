#pragma once

#include <string>
#include <iostream>

namespace ecs {
	enum ComponentType {
		None = 1 << 0,
		Transform = 1 << 1
	};

	class BaseComponent {
	public:
		friend bool operator==(const BaseComponent& lhs, const BaseComponent& rhs) { return lhs.m_name == rhs.m_name; }
		friend bool operator!=(const BaseComponent& lhs, const BaseComponent& rhs) { return !(lhs.m_name == rhs.m_name); }
		friend bool operator<(const BaseComponent& lhs, const BaseComponent& rhs) { return (int)lhs.m_type < (int)rhs.m_type; }
		friend bool operator>(const BaseComponent& lhs, const BaseComponent& rhs) { return (int)lhs.m_type > (int)rhs.m_type; }

		virtual inline const ComponentType getType() { return m_type; }
		virtual inline const std::string& getName() { return m_name; }
		virtual inline const bool isComponentUnique() { return m_isUnique; }

	protected:
		ComponentType m_type = ComponentType::None;

		std::string m_name = "Undefined";	// TODO: Use Hash to speed up operations?
		bool m_isUnique = true;				// If this is True the Component cannot be added twice to an Entity
	};
}