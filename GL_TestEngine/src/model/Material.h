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
	class Material {
	public:
		Material(const aiScene& scene, const aiMesh& mesh);
		~Material();

		const inline aiMaterial* getMaterial() { return m_material; }

	private:
		void loadMaterialTextures(aiTextureType type, const std::string& typeName);

		std::vector<Texture*> m_textures;

		aiMaterial* m_material = nullptr;
	};
}