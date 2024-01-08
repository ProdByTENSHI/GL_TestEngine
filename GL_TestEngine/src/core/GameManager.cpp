#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "Shader.h"
#include "ResourceManager.h"
#include "ecs/ECS.h"
#include "ecs/Components.h"

namespace core {
	Shader* shader = nullptr;
	ecs::Entity* entity = nullptr;

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

		entity = &ecs::EntityManager::getInstance()->createEmptyEntity();
		ecs::EntityManager::getInstance()->addComponent(entity->getId(), new ecs::TransformComponent(glm::vec3(100.0f, 100.0f, 50.0f)));
		ecs::EntityManager::getInstance()->addComponent(entity->getId(), new ecs::MeshComponent("res/models/test.obj", *shader));

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		delete ecs::EntityManager::getInstance();

		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();

		logger::Logger::getInstance()->write("Engine Closed!");

		delete logger::Logger::getInstance();
	}

	void GameManager::update() {
		while (!glfwWindowShouldClose(m_window->getWindow())) {
			ecs::EntityManager::getInstance()->update();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ecs::EntityManager::getInstance()->render();

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
		}
	}
}