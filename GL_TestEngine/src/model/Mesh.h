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
		GLfloat position[3];			// X, Y, Z, 12 Bytes - Offset: 0
		GLfloat textureCoords[2];	// UVs, 8 Bytes  - Offset: 12
		GLfloat normal[3];			// X, Y, Z 12 Bytes - Offset 20
	};

	class Mesh {
	public:
		Mesh(const std::string& meshPath);
		~Mesh();

		// Load all Meshes and the corresponding Texture and put them in the m_meshes vector
		void loadMesh(const std::string& path);

		// Load all Informations from the Mesh into the Vectors
		void processMesh(aiMesh* mesh);

		// Getter
		const memory::VAO& getVao() { return m_vao; }
		const std::vector<GLuint>& getIndices() { return m_indices; }

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