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
#include "utility/ContainerUtility.h"
#include "math/Random.h"

namespace engine {
	const int BOXES_IN_SCENE = 5;

	Shader* shader = nullptr;
	Entity* ambient = nullptr;
	Entity* directional = nullptr;
	Entity* entity = nullptr;

	DebugUI* debugUi = nullptr;

	GameManager::GameManager() {
		if (!glfwInit()) {
			Logger::getInstance()->write(std::string("Could not initialize GLFW. Error: " + glfwGetError(NULL)));
			return;
		}

		m_window = new Window();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		// Initialize GLEW after creating the OpenGL Context
		if (glewInit() != GLEW_OK) {
			Logger::getInstance()->write("GLEW could not be initialized!");
			return;
		}

		debugUi = new DebugUI(*m_window);

		shader = new Shader("res/shader/shader.vert", "res/shader/shader.frag");
		m_camera = new Camera(45.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f), m_window->getWidth(), m_window->getHeight(), *shader);

		ambient = &EntityManager::getInstance()->createEmptyEntity();
		EntityManager::getInstance()->addComponent(ambient->getId(), new AmbientLightComponent(1.0f, 1.0f, 1.0f, 1.0f, *shader));

		directional = &EntityManager::getInstance()->createEmptyEntity();
		TransformComponent* directionalTransform = (TransformComponent*)EntityManager::getInstance()->addComponent(directional->getId(), 
			new TransformComponent("u_LightPosition", glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		EntityManager::getInstance()->addComponent(directional->getId(), new ModelComponent("res/models/box-large.obj", *shader));
		EntityManager::getInstance()->addComponent(directional->getId(), new DirectionalLightComponent(0.5f, 0.5f, 1.0f, 1.0f, *directionalTransform, *shader));

		entity = &EntityManager::getInstance()->createEmptyEntity();
		EntityManager::getInstance()->addComponent(entity->getId(), new TransformComponent("u_ObjectTransform", glm::vec3(0), glm::vec3(0), glm::vec3(1)));
		EntityManager::getInstance()->addComponent(entity->getId(), new ModelComponent("res/models/box-large.obj", *shader));

		m_isRunning = true;
	}

	GameManager::~GameManager() {
		delete m_camera;
		delete shader;
		delete EntityManager::getInstance();
		delete debugUi;

		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();

		delete m_window;

		Logger::getInstance()->write("Engine Closed!");
		delete Logger::getInstance();
	}

	void GameManager::update() {
		float lastFrameTime = 0.0f;
		//glClearColor(0.1f, 0.1, 0.1, 1.0f);

		AmbientLightComponent* ambientLight = (AmbientLightComponent*)EntityManager::getInstance()->getComponentByType(*ambient, ComponentType::AmbientLightType);
		TransformComponent* transform = (TransformComponent*)EntityManager::getInstance()->getComponentByType(*entity, ComponentType::TransformType);

		TransformComponent* lightTransform = (TransformComponent*)EntityManager::getInstance()->getComponentByType(*directional, ComponentType::DirectionalLightType);

		while (!glfwWindowShouldClose(m_window->getWindow())) {
			Time::onUpdateStart();
			glfwPollEvents();

			if (Time::getTime() - Time::getLastFrameTime() >= m_FRAMERATECAP) {
				transform->rotate(Y_AXIS, Time::getDeltaTime());

				ambientLight->setValues(*debugUi->m_ambientColorR, *debugUi->m_ambientColorG, *debugUi->m_ambientColorB, *debugUi->m_ambientIntensity);

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				m_camera->HandleInput(*m_window->getWindow(), 5.0f);
				m_camera->CalculateView();

				Time::onRenderStart();
				EntityManager::getInstance()->render(*shader);

				// Only show Debug UI when in Debug Mode
				// Do this after drawing Entities to avoid the Entities overlapping the UI
#ifndef NDEBUG
				debugUi->render();
				if (debugUi->shouldShowWireFrame())
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

				glfwSwapBuffers(m_window->getWindow());
				Time::onRenderEnd();
			}

			Time::onUpdateEnd();
		}
	}
}