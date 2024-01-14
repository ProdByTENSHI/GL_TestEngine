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

		Window* m_window = nullptr;
		Camera* m_camera = nullptr;
	};
}