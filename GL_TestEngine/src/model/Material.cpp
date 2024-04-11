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

		loadMaterialTextures(aiTextureType_AMBIENT, "texture_ambient");
		loadMaterialTextures(aiTextureType_DIFFUSE, "texture_diffuse");
		loadMaterialTextures(aiTextureType_SPECULAR, "texture_specular");

		std::cout << m_material->GetName().C_Str() << std::endl;

		aiColor3D ambientColor;
		aiColor3D diffuseColor;
		aiColor3D specularColor;

		m_material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
		m_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
		m_material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
	
		m_data.ambient = colorToVec(ambientColor);
		m_data.diffuse = colorToVec(diffuseColor);
		m_data.specular = colorToVec(specularColor);

		// Make sure the Material Values are not 0 because this will fuck up the Shader
		std::cout << "AMBIENT: " << m_data.ambient.x << " " << m_data.ambient.y << " " << m_data.ambient.z << std::endl;
		std::cout << "DIFFUSE: " << m_data.diffuse.x << " " << m_data.diffuse.y << " " << m_data.diffuse.z << std::endl;
		std::cout << "SPECULAR: " << m_data.specular.x << " " << m_data.specular.y << " " << m_data.specular.z << std::endl;

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
			aiString path;
			m_material->GetTexture(type, i, &path);

			std::string finalPath = std::string("res/" + std::string(path.C_Str()));

			// Load the Texture from the given Path either from the Cache or the Filesystem
			Texture* texture = ResourceManager::getInstance()->loadTexture(finalPath, typeName);
		}
	}

	const glm::vec3& Material::colorToVec(const aiColor3D& color) {
		glm::vec3 vec;

		vec.x = color.r;
		vec.y = color.g;
		vec.z = color.b;

		return vec;
	}
}