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

	Model* ResourceManager::loadModel(const std::string& path) {
		if (doesResourceExist(m_models, path)) {
			return m_models[path];
		}
		else {
			Model* model = new Model(path);
			if (!model->wasLoaded())
				return nullptr;

			m_models.insert(std::make_pair(path, model));
			return model;
		}
	}

	Texture* ResourceManager::loadTexture(const std::string& path, const std::string& type) {
		if (doesResourceExist(m_textures, path)) {
			return m_textures[path];
		}
		else {
			Texture* texture = new Texture(path, type);
			if (texture == nullptr)
				return nullptr;

			cacheTexture(*texture);
			return texture;
		}
	}

	void ResourceManager::cacheTexture(Texture& texture) {
		if (m_textures[texture.getTextureData().path] != nullptr) {
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