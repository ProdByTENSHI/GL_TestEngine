#include "ResourceManager.h"

#include "logger/Logger.h"

namespace core {
	static ResourceManager* instance;

	ResourceManager::ResourceManager() { }

	ResourceManager* ResourceManager::getInstance() {
		if (instance == nullptr)
			instance = new ResourceManager();

		return instance;
	}

	model::Texture* ResourceManager::loadTexture(const std::string& path) {
		if (doesResourceExist(m_textures, path)) {
			logger::Logger::getInstance()->write(std::string("Texture " + path + " was already loaded before."));
			return m_textures[path];
		}
		else {
			logger::Logger::getInstance()->write(std::string("Texture " + path + " was not loaded before."));
			model::Texture* texture = new model::Texture(path);
			if (texture == nullptr)
				return nullptr;

			m_textures.insert(std::make_pair(path, texture));

			return texture;
		}
	}

	const std::unordered_map<std::string, model::Texture*>& ResourceManager::getTextures() {
		return m_textures;
	}

	template<typename T> bool ResourceManager::doesResourceExist(const std::unordered_map<std::string, T>& map, const std::string& path) {
		return map.find(path) != map.end();
	}
}