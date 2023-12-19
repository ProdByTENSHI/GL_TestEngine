#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Shader.h"
#include "ResourceManager.h"
#include "ecs/ECS.h"

namespace core {
	Shader* shader = nullptr;
	ecs::Entity* entity[5];

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

		shader = new Shader("res/shader/shader.vert", "res/shader/shader.frag");

		for (unsigned int i = 0; i < 5; i++) {
			entity[i] = ecs::EntityManager::getInstance()->createEmptyEntity();
		}

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();

		logger::Logger::getInstance()->write("Game Closed!");
	}

	void GameManager::update() {
		while (!glfwWindowShouldClose(m_window->getWindow())) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
		}
	}
}