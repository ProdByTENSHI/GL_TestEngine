#pragma once

namespace engine {
	class RenderComponent {
	public:
		virtual void render(Shader& shader) { }
	};
}