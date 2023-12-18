#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include "core/Shader.h"
#include "Texture.h"

#include "memory/VBO.h"
#include "memory/VAO.h"
#include "memory/IBO.h"

namespace model {
	// Total Bytes per Vertex: 32
	struct VertexData {
		glm::vec3 position;			// X, Y, Z, 12 Bytes - Offset: 0
		glm::vec2 textureCoords;	// UVs, 8 Bytes  - Offset: 12
		glm::vec3 normal;			// X, Y, Z 12 Bytes - Offset 20
	};

	class Mesh {
	public:
		Mesh(const std::string& meshPath);
		~Mesh();

		// Load all Meshes and the corresponding Texture and put them in the m_meshes vector
		void loadMesh(const std::string& path);

		// Load all Informations from the Mesh into the Vectors
		void processMesh(aiMesh* mesh);
		void render(core::Shader& shader);

	private:
		const aiScene* m_scene = nullptr;

		std::vector<VertexData> m_verticeData;
		std::vector<aiMesh*> m_meshes;
		std::vector<GLuint> m_indices;

		memory::VBO m_vbo;
		memory::VAO m_vao;
		memory::IBO m_ibo;
		memory::VertexBufferLayout m_layout;
	};
}