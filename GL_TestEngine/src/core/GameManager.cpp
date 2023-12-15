#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Shader.h"

namespace core {
	model::Model* model;

	GameManager::GameManager() {
		if (!glfwInit()) {
			std::cout << "Could not initialize GLFW. Error: " << glfwGetError(NULL) << std::endl;
			return;
		}

		m_window = new Window();

		// Initialize GLEW after creating the OpenGL Context
		if (glewInit() != GLEW_OK) {
			std::cout << "GLEW could not be initialized!";
			return;
		}

		glEnable(GL_DEPTH_TEST);

		model = new model::Model("res/models/test.obj", "res/textures/wall.jpg");

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();
	}

	void GameManager::update() {
		while (!glfwWindowShouldClose(m_window->getWindow())) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			model->render();

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
		}
	}
}