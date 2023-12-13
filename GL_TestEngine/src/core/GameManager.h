#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "core/Window.h"
#include "camera/Camera.h"

namespace core {
	class GameManager {
	public:
		GameManager();
		~GameManager();

		void update();

	private:
		// STATES
		bool m_isRunning = false;

		Window* m_window = nullptr;
		camera::Camera* m_mainCamera = nullptr;
	};
}