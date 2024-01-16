#include "Material.h"

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

		std::string name = m_material->GetName().C_Str();
		Logger::getInstance()->write("Material loaded: " + name);
	}

	Material::~Material() {
		delete m_material;
	}

	void Material::loadMaterialTextures(aiTextureType type, const std::string& typeName) {
		for (int i = 0; i < m_material->GetTextureCount(type); i++) {
			// Outputs the Texture Path of the current Iteration to &path
			aiString path;
			m_material->GetTexture(type, i, &path);		

			// Load the Texture from the given Path either from the Cache or the Filesystem
			Texture* texture = ResourceManager::getInstance()->loadTexture(path.C_Str(), typeName);
		}
	}
}