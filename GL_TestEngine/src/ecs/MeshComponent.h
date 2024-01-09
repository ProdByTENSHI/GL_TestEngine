#pragma once

#include <string>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "model/Mesh.h"
#include "core/Shader.h"

namespace ecs {
	class MeshComponent : public BaseComponent, public RenderComponent {
	public:
		MeshComponent(model::Mesh* mesh, core::Shader& shader) { m_mesh = mesh; m_shader = &shader; }
		MeshComponent(const std::string& path, core::Shader& shader) { m_mesh = new model::Mesh(path); m_shader = &shader; }

		void render(glm::vec3 position, const char* positionUniform) override;

		inline const ComponentType getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		ComponentType m_type = ComponentType::Mesh;

		const std::string m_name = "Mesh Component";
		const bool m_isUnique = true;

	private:
		model::Mesh* m_mesh = nullptr;
		core::Shader* m_shader = nullptr;
	};
}