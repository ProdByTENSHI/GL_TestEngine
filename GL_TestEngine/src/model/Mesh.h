#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture.h"
#include "memory/VBO.h"
#include "memory/VAO.h"
#include "memory/IBO.h"

namespace model {
	// Total Bytes per Vertex: 42
	struct VertexData {
		GLfloat position[3];			// X, Y, Z, 12 Bytes - Offset: 0
		GLfloat color[4];				// RGBA, 24 Bytes - Offset: 12
		GLfloat textureCoords[2];		// UV.x, UV.y, 8 Bytes  - Offset: 36
	};

	class Mesh {
	public:
		Mesh(const std::string& path);
		~Mesh();

		void loadMesh(const std::string& path);
		void loadTexture(const std::string& path);
		void processMesh(aiMesh* mesh);
		void render();

	private:
		const aiScene* m_scene = nullptr;

		std::vector<VertexData> m_vertices;
		std::vector<aiMesh*> m_meshes;
		std::vector<unsigned int> m_indices;

		Texture* m_texture = nullptr;

		memory::VBO m_vbo;
		memory::VAO m_vao;
		memory::IBO m_ibo;
		memory::VertexBufferLayout m_layout;
	};
}