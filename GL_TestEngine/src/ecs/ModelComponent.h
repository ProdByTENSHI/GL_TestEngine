#pragma once

#include <string>

#include "BaseComponent.h"
#include "RenderComponent.h"

#include "core/ResourceManager.h"
#include "model/Model.h"
#include "renderer/Shader.h"

namespace engine {
	class ModelComponent : public BaseComponent, public RenderComponent {
	public:
		ModelComponent(Model* model, Shader& shader) {
			m_model = model;
			m_shader = &shader;
		}

		ModelComponent(const std::string& meshPath, Shader& shader) {
			m_model = ResourceManager::getInstance()->loadModel(meshPath); 
			m_shader = &shader;
		}

		void render() override {
			m_model->render(*m_shader);
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
		Shader* m_shader = nullptr;
	};
}