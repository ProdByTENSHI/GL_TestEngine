#pragma once

#include <unordered_map>
#include <string>

#include <model/Model.h>
#include "model/Texture.h"

namespace engine {
	class ResourceManager {
	public:
		static ResourceManager* getInstance();
		
		Model* loadModel(const std::string& path);
		Texture* loadTexture(const std::string& path, const std::string& type);

		// Caches the Texture into the m_textures map
		void cacheTexture(Texture& texture);

		const std::unordered_map<std::string, Texture*>& getTextures();
		template<typename T> bool doesResourceExist(const std::unordered_map<std::string, T>& map, const std::string& path);

	private:
		ResourceManager();
		ResourceManager(const ResourceManager& other);

		// K: Path; V: Pointer to Resource
		std::unordered_map<std::string, Texture*> m_textures;
		std::unordered_map<std::string, Model*> m_models;
	};
}