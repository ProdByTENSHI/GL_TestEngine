#pragma once

#include <string>

namespace ecs {
	class BaseComponent {
	public:
		std::string name = "Undefined";

		bool operator==(const BaseComponent& rhs) {
			return name == rhs.name;
		}
	};
}