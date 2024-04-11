#include "Application.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

#include "logger/Logger.h"
#include "renderer/Shader.h"
#include "ecs/ECS.h"
#include "time/Time.h"

namespace engine {
	Application::Application(const std::string& title, int width, int height) {
		if (!glfwInit()) {
			Logger::getInstance()->write(std::string("Could not initialize GLFW. Error: " + glfwGetError(NULL)));
			return;
		}

		m_window = new Window();
		m_window->create(title, width, height);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		// Initialize GLEW after creating the OpenGL Context
		if (glewInit() != GLEW_OK) {
			Logger::getInstance()->write("GLEW could not be initialized!");
			return;
		}

		m_defaultShader = new Shader("res/shader/shader.vert", "res/shader/shader.frag");

		m_isRunning = true;

		for (const auto& script : m_callStack) {
			script->onAppStart();
		}
	}

	Application::~Application() {
		glfwDestroyWindow(m_window->getWindow());
		glfwTerminate();

		delete m_window;

		Logger::getInstance()->write("Engine Closed!");
		delete Logger::getInstance();
	}

	void Application::addToCallStack(ScriptLifeTime* script) {
		m_callStack.push_back(script);
	}

	void Application::update() {
		float lastFrameTime = 0.0f;

		while (!glfwWindowShouldClose(m_window->getWindow())) {
			glfwPollEvents();

			for (const auto& script : m_callStack) {
				script->onUpdate();
			}

			if (Time::getTime() - Time::getLastFrameTime() >= m_window->getFramerateCap()) {
				EntityManager::getInstance()->update(*m_defaultShader);
			}

			Time::onUpdateEnd();
			render();
		}
	}

	void Application::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		Time::onRenderStart();
		EntityManager::getInstance()->render(*m_defaultShader);
		for (const auto& script : m_callStack) {
			script->onRender();
		}

		glfwSwapBuffers(m_window->getWindow());
		Time::onRenderEnd();

		update();
	}
}