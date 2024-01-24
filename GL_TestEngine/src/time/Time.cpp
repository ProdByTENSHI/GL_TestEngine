#include "Time.h"

#include <GLFW/glfw3.h>

namespace engine {
	float Time::updateStartTime = 0.0f;
	float Time::lastFrameTime = 0.0f;
	int Time::renderedFrames = 0;

	float Time::getTime() {
		return glfwGetTime();
	}

	float Time::getFPS() {
		return 1.0f / getDeltaTime();
	}

	float Time::getDeltaTime() {
		return updateStartTime - lastFrameTime;
	}

	void Time::onUpdateStart() {
		updateStartTime = glfwGetTime();
	}

	void Time::onUpdateEnd() { }

	void Time::onRenderStart() { }

	void Time::onRenderEnd() {
		lastFrameTime = getTime();
		++renderedFrames;
	}
}