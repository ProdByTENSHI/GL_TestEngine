// HANDLES MATERIAL LOADING AND THE ASSOCIATED TEXTURES
#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/vec3.hpp>

#include "Texture.h"

namespace engine {
	struct MaterialData {
		float ambient;
		float diffuse;
		float specular;
		float shininess;
	};

	class Material {
	public:
		Material(const aiScene& scene, const aiMesh& mesh);
		Material(const MaterialData& data);
		~Material();

		const inline aiMaterial* getMaterial() { return m_material; }
		const inline MaterialData getData() const { return m_data; }
		const inline std::vector<Texture*> getTextures() { return m_textures; }

	private:
		MaterialData m_data;

		void loadMaterialTextures(aiTextureType type, const std::string& typeName);

		std::vector<Texture*> m_textures;

		aiMaterial* m_material = nullptr;
	};
}