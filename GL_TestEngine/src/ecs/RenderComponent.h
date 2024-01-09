#pragma once

#include <glm/glm.hpp>

namespace ecs {
	class RenderComponent {
	public:
		virtual void render(glm::vec3 position, const char* positionUniform) { }
	};
}