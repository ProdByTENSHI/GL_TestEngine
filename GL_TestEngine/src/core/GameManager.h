#pragma once

#include "core/Window.h"
#include "logger/Logger.h"
#include "camera/Camera.h"

namespace engine {
	class GameManager {
	public:
		GameManager();
		~GameManager();

		void update();

		const inline Window& getWindow() { return *m_window; }

	private:
		// STATES
		bool m_isRunning = false;

		// TODO: Move Framerate Cap to Window Class
		const float m_FRAMERATECAP = 1.0f / 60.0f;

		Window* m_window = nullptr;
		Camera* m_camera = nullptr;
	};
}