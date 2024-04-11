#pragma once

#include <list>
#include <functional>

#include "ScriptLifeTime.h"
#include "renderer/Shader.h"
#include "core/Window.h"

namespace engine {
	class Application {
	public:
		Application(const std::string& title, int width, int height);
		~Application();

		void addToCallStack(ScriptLifeTime* script);

		void update();
		void render();

		inline Window& getWindow() { return *m_window; }
		inline Shader& getShader() { return *m_defaultShader; }

	private:
		// STATES
		bool m_isRunning = false;

		// STACKS
		std::list<ScriptLifeTime*> m_callStack;

		// COMPONENTS
		Window* m_window = nullptr;
		Shader* m_defaultShader = nullptr;
	};
}