#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "model/Mesh.h"
#include "Shader.h"

namespace core {
	Shader shader;
	model::Mesh* mesh = nullptr;

	GameManager::GameManager() {
		if (!glfwInit()) {
			logger::Logger::getInstance()->write(std::string("Could not initialize GLFW. Error: " + glfwGetError(NULL)));
			return;
		}

		m_window = new Window();

		// Initialize GLEW after creating the OpenGL Context
		if (glewInit() != GLEW_OK) {
			logger::Logger::getInstance()->write("GLEW could not be initialized!");
			return;
		}

		glEnable(GL_DEPTH_TEST);

		shader = Shader("res/shader/shader.vert", "res/shader/shader.frag");
		mesh = new model::Mesh("res/models/test.obj");

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();

		logger::Logger::getInstance()->write("QUIT APPLICATION");
	}

	void GameManager::update() {
		while (!glfwWindowShouldClose(m_window->getWindow())) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			mesh->render(shader);

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
		}
	}
}