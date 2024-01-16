#include "ResourceManager.h"

#include "logger/Logger.h"

namespace engine {
	static ResourceManager* instance;

	ResourceManager::ResourceManager() { }

	ResourceManager* ResourceManager::getInstance() {
		if (instance == nullptr)
			instance = new ResourceManager();

		return instance;
	}

	Texture* ResourceManager::loadTexture(const std::string& path, const std::string& type) {
		if (doesResourceExist(m_textures, path)) {
			Logger::getInstance()->write(std::string("Texture " + path + " was already loaded before."));
			return m_textures[path];
		}
		else {
			Logger::getInstance()->write(std::string("Texture " + path + " was not loaded before."));
			Texture* texture = new Texture(path, type);
			if (texture == nullptr)
				return nullptr;

			cacheTexture(*texture);
			return texture;
		}
	}

	void ResourceManager::cacheTexture(Texture& texture) {
		if (m_textures[texture.getTextureData().path] == nullptr) {
			Logger::getInstance()->write(texture.getTextureData().path + " was already cached!");
			return;
		}

		m_textures.insert(std::make_pair(texture.getTextureData().path, &texture));
	}

	const std::unordered_map<std::string, Texture*>& ResourceManager::getTextures() {
		return m_textures;
	}

	template<typename T> bool ResourceManager::doesResourceExist(const std::unordered_map<std::string, T>& map, const std::string& path) {
		return map.find(path) != map.end();
	}
}