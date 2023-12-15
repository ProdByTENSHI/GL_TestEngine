#include "Model.h"

#include <iostream>
#include <GL/glew.h>

namespace model {
	Model::Model(const std::string& meshPath, const std::string& texPath) {
		m_shader = std::make_shared<core::Shader>("res/shader/model.vert", "res/shader/model.frag");

		loadMesh(meshPath);
		loadTexture(texPath);
	}

	Model::~Model() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Model::loadMesh(const std::string& path) {
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType
		);

		if (scene == nullptr) {
			std::cerr << "Could not load Mesh from path " << path << std::endl;
			return;
		}

		m_scene = scene;

		// Process all Meshes and put them in the m_meshes Vector
		for (int i = 0; i < m_scene->mNumMeshes; i++) {
			processMesh(m_scene->mMeshes[i]);

			m_meshes.push_back(m_scene->mMeshes[i]);
		}

		m_layout.push<GLfloat>(3);	// Position
		m_layout.push<GLfloat>(3);	// Color
		m_layout.push<GLfloat>(2);	// Texture Coords

		m_vao.addBuffer(m_vbo, m_layout);

		m_vbo.putData(m_vertices.data(), m_vertices.size() * sizeof(VertexData));
		m_ibo.putData(m_indices.data(), m_indices.size());

		m_vbo.unbind();
	}

	void Model::loadTexture(const std::string& path) {
		m_texture = std::make_shared<Texture>(path);
	}

	void Model::processMesh(aiMesh* mesh) {
		VertexData tempData;

		// Convert Vertex Position, Color and Texture Coords to Vertex Data
		for (int i = 0; i < mesh->mNumVertices; i++) {
			tempData.position[0] = mesh->mVertices[i].x;
			tempData.position[1] = mesh->mVertices[i].y;
			tempData.position[2] = mesh->mVertices[i].z;

			// For now just set Color to white
			tempData.color[0] = 1.0f;
			tempData.color[1] = 1.0f;
			tempData.color[2] = 1.0f;

			if (!mesh->HasTextureCoords(0)) {
				tempData.textureCoords[0] = 0.0f;
				tempData.textureCoords[0] = 0.0f;
			}

			tempData.textureCoords[0] = mesh->mTextureCoords[0][i].x;
			tempData.textureCoords[1] = mesh->mTextureCoords[0][i].y;

			m_vertices.push_back(tempData);
		}

		// Get Indices and place them into m_indices Vector
		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++) {
				m_indices.push_back(face.mIndices[j]);
			}
		}
	}

	void Model::render() {
		m_shader->bind();
		m_texture->bind();
		m_vao.bind();
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	}
}