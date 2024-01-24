#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "BaseComponent.h"
#include "RenderComponent.h"
#include "UpdateComponent.h"

#include "core/ResourceManager.h"
#include "model/Texture.h"
#include "renderer/Shader.h"

namespace engine {
	class TextureComponent : public BaseComponent, public RenderComponent {
	public:
		TextureComponent(const std::string& path, const std::string& type, unsigned int textureSlot = 0) {
			m_texture = ResourceManager::getInstance()->loadTexture(path, type);
			m_textureSlot = textureSlot;
		}

		void render() override {
			m_texture->bind(m_textureSlot);
		}

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		unsigned int m_type = ComponentType::RenderType | ComponentType::TextureType;

		const std::string m_name = "Texture Component";
		const bool m_isUnique = false;

	private:
		Texture* m_texture = nullptr;
		unsigned int m_textureSlot;
	};
}