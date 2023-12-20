#pragma once

#include <string>
#include <iostream>

namespace ecs {
	class BaseComponent {
	public:
		std::string name = "Undefined";

		friend bool operator==(const BaseComponent& lhs, const BaseComponent& rhs) { return rhs.getId() == lhs.getId(); }
		friend bool operator!=(const BaseComponent& lhs, const BaseComponent& rhs) { return !(rhs.getId() == lhs.getId()); }
		friend bool operator<(const BaseComponent& lhs, const BaseComponent& rhs) { return !(rhs.getId() < lhs.getId()); }
		friend bool operator>(const BaseComponent& lhs, const BaseComponent& rhs) { return !(rhs.getId() > lhs.getId()); }

		inline unsigned int getId() const { return m_id; }

	protected:
		unsigned int m_id = 0;	// 0 reserved for the BaseComponent
	};
}