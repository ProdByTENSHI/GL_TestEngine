#include "Time.h"

#include <GLFW/glfw3.h>

namespace engine {
	float Time::updateStartTime = 0.0;
	float Time::deltaTime = 0.0;

	float Time::getTime() {
		return glfwGetTime();
	}

	// TODO: Fix this
	float Time::getFPS() {
		return 1000.0f / deltaTime;
	}

	void Time::onUpdateStart() {
		updateStartTime = glfwGetTimerValue();
	}

	void Time::onUpdateEnd() {
		deltaTime = (glfwGetTimerValue() - updateStartTime) / glfwGetTimerFrequency();
	}
}