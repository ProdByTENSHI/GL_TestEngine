#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include "renderer/Shader.h"
#include "Texture.h"

#include "memory/VBO.h"
#include "memory/VAO.h"
#include "memory/IBO.h"

namespace engine {
	// Total Bytes per Vertex: 32
	struct VertexData {
		GLfloat position[3];			// X, Y, Z, 12 Bytes - Offset: 0
		GLfloat textureCoords[2];		// UVs, 8 Bytes  - Offset: 12
		GLfloat normal[3];				// X, Y, Z 12 Bytes - Offset 20
	};

	class Mesh {
	public:
		Mesh(const std::string& meshPath);
		~Mesh();

		// Load all Meshes and the corresponding Texture and put them in the m_meshes vector
		void loadMesh(const std::string& path);

		// Load all Informations from the Mesh into the Vectors
		void processMesh(aiMesh* mesh);

		void render(Shader& shader);

	private:
		const aiScene* m_scene = nullptr;

		std::vector<VertexData> m_verticeData;
		std::vector<aiMesh*> m_meshes;
		std::vector<GLuint> m_indices;

		VBO m_vbo;
		VAO m_vao;
		IBO m_ibo;
		VertexBufferLayout m_layout;
	};
}