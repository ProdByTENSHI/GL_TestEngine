#pragma once

#include <unordered_map>
#include <string>

#include "model/Texture.h"

namespace core {
	class ResourceManager {
	public:
		static ResourceManager* getInstance();

		model::Texture* loadTexture(const std::string& path);

		const std::unordered_map<std::string, model::Texture*>& getTextures();
		template<typename T> bool doesResourceExist(const std::unordered_map<std::string, T>& map, const std::string& path);

	private:
		ResourceManager();
		ResourceManager(const ResourceManager& other);

		// K: Path; V: Pointer to Texture
		std::unordered_map<std::string, model::Texture*> m_textures;
	};
}