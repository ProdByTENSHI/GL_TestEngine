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

	private:
		// STATES
		bool m_isRunning = false;

		// APPLICATION CONSTANTS
		const float m_MAX_FPS = 1.0 / 120.0f;

		Window* m_window = nullptr;
		Camera* m_camera = nullptr;
	};
}