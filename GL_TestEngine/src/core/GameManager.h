#pragma once

#include "core/Window.h"
#include "logger/Logger.h"

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
	};
}