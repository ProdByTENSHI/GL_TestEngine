#include "Mesh.h"

#include <iostream>
#include <GL/glew.h>

namespace model {
	Mesh::Mesh(const std::string& path) {
		loadMesh(path);
	}

	Mesh::~Mesh() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		delete m_texture;
	}

	void Mesh::loadMesh(const std::string& path) {
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

		m_layout.push<GLfloat>(3);
		m_layout.push<GLfloat>(4);
		m_layout.push<GLfloat>(2);
		m_vao.addBuffer(m_vbo, m_layout);

		m_vbo.putData(m_vertices.data(), m_vertices.size() * sizeof(VertexData));
		m_ibo.putData(m_indices.data(), m_indices.size());

		m_vbo.unbind();
	}

	void Mesh::loadTexture(const std::string& path) {
		m_texture = new Texture(path);
		m_texture->bind();
	}

	void Mesh::processMesh(aiMesh* mesh) {
		VertexData tempData;

		// Convert Vertex Position and Texture Coords to Vertex Data
		for (int i = 0; i < mesh->mNumVertices; i++) {
			tempData.position[0] = mesh->mVertices[i].x;
			tempData.position[1] = mesh->mVertices[i].y;
			tempData.position[2] = mesh->mVertices[i].z;

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

	void Mesh::render() {
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	}
}