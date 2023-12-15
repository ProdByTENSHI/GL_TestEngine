#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/Shader.h"
#include "Texture.h"

#include "memory/VBO.h"
#include "memory/VAO.h"
#include "memory/IBO.h"

namespace model {
	// Total Bytes per Vertex: 32
	struct VertexData {
		GLfloat position[3];			// X, Y, Z, 12 Bytes - Offset: 0
		GLfloat color[3];				// R, G, B 12 Bytes - Offset: 12
		GLfloat textureCoords[2];		// UV.x, UV.y, 8 Bytes  - Offset: 24
	};

	class Model {
	public:
		Model(const std::string& meshPath, const std::string& texPath);
		~Model();

		// Load all Meshes and the corresponding Texture and put them in the m_meshes vector
		void loadMesh(const std::string& path);
		void loadTexture(const std::string& path);

		// Load all Informations from the Mesh into the Vectors
		void processMesh(aiMesh* mesh);
		void render();

	private:
		const aiScene* m_scene = nullptr;

		std::vector<VertexData> m_vertices;
		std::vector<aiMesh*> m_meshes;
		std::vector<unsigned int> m_indices;
		
		std::shared_ptr<Texture> m_texture = nullptr;
		std::shared_ptr<core::Shader> m_shader = nullptr;

		memory::VBO m_vbo;
		memory::VAO m_vao;
		memory::IBO m_ibo;
		memory::VertexBufferLayout m_layout;
	};
}