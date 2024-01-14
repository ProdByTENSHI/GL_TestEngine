#pragma once

#include <string>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "model/Mesh.h"
#include "renderer/Shader.h"

namespace engine {
	class MeshComponent : public BaseComponent, public RenderComponent {
	public:
		MeshComponent(Mesh* mesh, Shader& shader) { m_mesh = mesh; m_shader = &shader; }
		MeshComponent(const std::string& path, Shader& shader) { m_mesh = new Mesh(path); m_shader = &shader; }

		void render() override;

		inline const ComponentType getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		ComponentType m_type = ComponentType::MeshType;

		const std::string m_name = "Mesh Component";
		const bool m_isUnique = true;

	private:
		Mesh* m_mesh = nullptr;
		Shader* m_shader = nullptr;
	};
}