#pragma once

#include <string>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "core/ResourceManager.h"
#include "model/Model.h"
#include "renderer/Shader.h"

namespace engine {
	class ModelComponent : public BaseComponent, public RenderComponent {
	public:
		ModelComponent(Model* model, TransformComponent& transform) {
			m_model = model;
			m_transform = &transform;
		}

		ModelComponent(const std::string& meshPath, TransformComponent& transform) {
			m_model = ResourceManager::getInstance()->loadModel(meshPath); 
			m_transform = &transform;
		}

		void render(Shader& shader) override {
			m_model->render(*m_shader);
		}

		void setShaderUniforms(Shader& shader) override {
			shader.setUniformMat4("u_ObjectTransform", m_transform->getTransformationMatrix());

			for (const auto& material : m_model->getMaterials()) {
				shader.setUniform1f("u_Material.ambient", material->getData().ambient);
				shader.setUniform1f("u_Material.diffuse", material->getData().diffuse);
			}
		}

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		unsigned int m_type = ComponentType::RenderType | ComponentType::ModelType;

		const std::string m_name = "Model Component";
		const bool m_isUnique = true;

	private:
		Model* m_model = nullptr;
		TransformComponent* m_transform = nullptr;
		Shader* m_shader = nullptr;
	};
}