#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "model/Mesh.h"
#include "Shader.h"

namespace core {
	Shader shader;
	model::Mesh* Mesh;

	GameManager::GameManager() {
		if (!glfwInit()) {
			std::cout << "Could not initialize GLFW. Error: " << glfwGetError(NULL) << std::endl;
			return;
		}

		m_window = new Window();

		// Initialize GLEW after creating the OpenGL Context
		if (glewInit() != GLEW_OK) {
			std::cout << "GLEW could be initialized!";
			return;
		}

		glEnable(GL_DEPTH_TEST);

		shader = Shader("res/shader/vertex.vert", "res/shader/fragment.frag");
		shader.bind();

		m_mainCamera = new camera::Camera(m_window->getWidth(), m_window->getHeight());

		Mesh = new model::Mesh("res/models/test.fbx");
		Mesh->loadTexture("res/textures/wall.jpg");
		shader.setUniform1i("u_Texture", 0);

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		delete m_mainCamera;
		delete Mesh;

		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();
	}

	void GameManager::update() {
		while (!glfwWindowShouldClose(m_window->getWindow())) {
			glClearColor(0xFF, 0x00, 0xEF, 0x00);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_mainCamera->HandleInput(m_window->getWindow());
			m_mainCamera->ViewMatrix(45.0f, 0.1f, 100.0f, shader, "u_CamMatrix");

			Mesh->render();

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
		}
	}
}