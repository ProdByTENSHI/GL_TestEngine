#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "renderer/Shader.h"
#include "ResourceManager.h"
#include "ecs/ECS.h"
#include "ecs/Components.h"

namespace engine {
	Shader* shader = nullptr;
	Entity* entity = nullptr;

	GameManager::GameManager() {
		if (!glfwInit()) {
			Logger::getInstance()->write(std::string("Could not initialize GLFW. Error: " + glfwGetError(NULL)));
			return;
		}

		m_window = new Window();

		// Initialize GLEW after creating the OpenGL Context
		if (glewInit() != GLEW_OK) {
			Logger::getInstance()->write("GLEW could not be initialized!");
			return;
		}

		glEnable(GL_DEPTH_TEST);

		shader = new Shader("res/shader/shader.vert", "res/shader/shader.frag");
		m_camera = new Camera(60.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f), m_window->getWidth(), m_window->getHeight(), *shader);

		entity = &EntityManager::getInstance()->createEmptyEntity();
		EntityManager::getInstance()->addComponent(entity->getId(), new TransformComponent(glm::vec3(1.0f, 5.0f, 0.0f)));
		EntityManager::getInstance()->addComponent(entity->getId(), new MeshComponent("res/models/ambulance.obj", *shader));

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		delete m_camera;
		delete shader;
		delete EntityManager::getInstance();

		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();

		delete m_window;

		Logger::getInstance()->write("Engine Closed!");

		delete Logger::getInstance();
	}

	void GameManager::update() {
		while (!glfwWindowShouldClose(m_window->getWindow())) {
			EntityManager::getInstance()->update(*shader);

			glClearColor(0.2f, 0.35f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			EntityManager::getInstance()->render();

			m_camera->CalculateMVP("u_CameraMatrix");

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
		}
	}
}