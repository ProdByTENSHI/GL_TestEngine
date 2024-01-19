#include "GameManager.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "renderer/Shader.h"
#include "ResourceManager.h"
#include "ecs/ECS.h"
#include "ecs/Components.h"
#include "ui/DebugUI.h"
#include "time/Time.h"

namespace engine {
	Shader* shader = nullptr;
	Entity* entity = nullptr;
	Entity* entity2 = nullptr;

	DebugUI* ui = nullptr;

	TransformComponent* transform = nullptr;
	TransformComponent* transform2 = nullptr;

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
		glEnable(GL_STENCIL_TEST);

		ui = new DebugUI(*m_window);

		shader = new Shader("res/shader/shader.vert", "res/shader/shader.frag");
		m_camera = new Camera(45.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f), m_window->getWidth(), m_window->getHeight(), *shader);

		entity = &EntityManager::getInstance()->createEmptyEntity();
		transform = (TransformComponent*)EntityManager::getInstance()->addComponent(entity->getId(), new TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		EntityManager::getInstance()->addComponent(entity->getId(), new ModelComponent("res/models/box-wide.obj", *shader));

		entity2 = &EntityManager::getInstance()->createEmptyEntity();
		transform2 = (TransformComponent*)EntityManager::getInstance()->addComponent(entity2->getId(), new TransformComponent(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		EntityManager::getInstance()->addComponent(entity2->getId(), new ModelComponent("res/models/structure-tall.obj", *shader));

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
		glClearColor(0.2f, 0.35f, 0.3f, 1.0f);

		while (!glfwWindowShouldClose(m_window->getWindow())) {
			Time::onUpdateStart();

			transform->translate(glm::vec3(0.0f, glm::cos(Time::getTime()) * Time::getDeltaTime(), 0.0f));
			transform->rotate(TransformComponent::Y_AXIS, 1.0f * Time::getDeltaTime());
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			EntityManager::getInstance()->render(*shader);

			// Only show Debug UI when in Debug Mode
#ifndef NDEBUG
			ui->render();
			if (ui->shouldShowWireFrame())
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

			m_camera->HandleInput(*m_window->getWindow(), 5.0f);
			m_camera->CalculateMVP();

			glfwSwapBuffers(m_window->getWindow());
			glfwPollEvents();
			Time::onUpdateEnd();
		}
	}
}