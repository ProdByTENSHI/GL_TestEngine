#pragma once

#include "renderer/Shader.h"

namespace engine {
	class UpdateComponent {
	public:
		virtual void update(Shader& shader) { }
	};
}