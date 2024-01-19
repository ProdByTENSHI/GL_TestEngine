#include "Material.h"

#include <iostream>

#include "core/ResourceManager.h"
#include "logger/Logger.h"

namespace engine {
	Material::Material(const aiScene& scene, const aiMesh& mesh) {
		if (mesh.mMaterialIndex < 0) {
			Logger::getInstance()->write("Invalid Material Index on Mesh!");
			return;
		}

		m_material = scene.mMaterials[mesh.mMaterialIndex];

		// Define here what Texture types to load -> For now use Phong
		loadMaterialTextures(aiTextureType_AMBIENT, "texture_ambient");
		loadMaterialTextures(aiTextureType_DIFFUSE, "texture_diffuse");
		loadMaterialTextures(aiTextureType_SPECULAR, "texture_specular");

		m_material->Get(AI_MATKEY_COLOR_AMBIENT, m_data.ambient);
		m_material->Get(AI_MATKEY_COLOR_DIFFUSE, m_data.diffuse);
		m_material->Get(AI_MATKEY_COLOR_SPECULAR, m_data.specular);

		std::cout << "MATERIAL DATA:" << std::endl;
		std::cout << "\tAmbient: " << m_data.ambient << std::endl;
		std::cout << "\tDiffuse: " << m_data.diffuse << std::endl;
		std::cout << "\tSpecular: " << m_data.specular << std::endl;

		std::string name = m_material->GetName().C_Str();
		Logger::getInstance()->write("Material loaded: " + name);
	}

	Material::Material(const MaterialData& data) {
		m_data = data;
	}

	Material::~Material() {
		delete m_material;
	}

	void Material::loadMaterialTextures(aiTextureType type, const std::string& typeName) {
		for (int i = 0; i < m_material->GetTextureCount(type); i++) {
			// Outputs the Texture Path of the current Iteration to &path
			aiString path;
			m_material->GetTexture(type, i, &path);

			std::string finalPath = std::string("res/" + std::string(path.C_Str()));

			// Load the Texture from the given Path either from the Cache or the Filesystem
			Texture* texture = ResourceManager::getInstance()->loadTexture(finalPath, typeName);
		}
	}
}