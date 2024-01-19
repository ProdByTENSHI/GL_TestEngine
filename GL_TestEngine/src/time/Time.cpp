#include "Time.h"

#include <GLFW/glfw3.h>

namespace engine {
	float Time::updateStartTime = 0.0f;
	float Time::deltaTime = 0.0f;
	float Time::lastFrameTime = 0.0f;
	int Time::renderedFrames = 0;

	float Time::getTime() {
		return glfwGetTime();
	}

	float Time::getFPS() {
		return renderedFrames / (getTime() - updateStartTime);
	}

	void Time::onUpdateStart() {
		updateStartTime = glfwGetTimerValue();
	}

	void Time::onUpdateEnd() {
		deltaTime = (glfwGetTimerValue() - updateStartTime) / glfwGetTimerFrequency();
	}

	void Time::onRenderStart() { }

	void Time::onRenderEnd() {
		lastFrameTime = getTime();
		++renderedFrames;
	}
}