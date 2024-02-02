#include "Model.h"

#include <iostream>
#include <GL/glew.h>

#include <stb_image.h>

#include "core/ResourceManager.h"
#include "logger/Logger.h"

namespace engine {
	unsigned int Model::triangleCount = 0;

	Model::Model(const std::string& meshPath) {
		loadModel(meshPath);
	}

	Model::~Model() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		for (const auto& material : m_materials) {
			delete material;
		}
	}

	void Model::loadModel(const std::string& path) {
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType
		);

		if (scene == nullptr) {
			Logger::getInstance()->write("Could not load Model from path " + path);
			return;
		}

		m_scene = scene;

		// Process all Meshes and put them in the m_meshes Vector
		for (int i = 0; i < m_scene->mNumMeshes; i++) {
			processMesh(m_scene->mMeshes[i]);
			m_meshes.push_back(m_scene->mMeshes[i]);
		}

		m_layout.push<GLfloat>(3);		// Position
		m_layout.push<GLfloat>(2);		// Texture Coords
		m_layout.push<GLfloat>(3);		// Normals

		m_vao.addBuffer(m_vbo, m_layout);

		m_vbo.putData(m_verticeData.data(), m_verticeData.size() * sizeof(VertexData));
		m_ibo.putData(m_indices.data(), m_indices.size());

		m_vbo.unbind();

		m_wasLoaded = true;
		Logger::getInstance()->write("Loaded Model " + path);
	}

	void Model::processMesh(aiMesh* mesh) {
		VertexData tempData;

		// Convert Vertex Position, Color and Texture Coords into the Vertex Data Struct Format
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

			tempData.normal[0] = mesh->mNormals[i].x;
			tempData.normal[1] = mesh->mNormals[i].y;
			tempData.normal[2] = mesh->mNormals[i].z;

			m_verticeData.push_back(tempData);

			// TODO: Wrong
			// Count Triangles
			if (i % 3 == 0) {
				Model::triangleCount++;
			}
		}

		// Get Indices and place them into m_indices Vector
		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (int j = 0; j < face.mNumIndices; j++) {
				m_indices.push_back(face.mIndices[j]);
			}
		}

		// Load Materials and the associated Textures
		if (mesh->mMaterialIndex >= 0) {
			Material* material = new Material(*m_scene, *mesh);
			m_materials.push_back(material);
		}
	}

	void Model::render(Shader& shader) {
		m_vao.addBuffer(m_vbo, m_layout);
		m_ibo.bind();

		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);

		m_ibo.unbind();
		m_vao.unbind();
	}
}