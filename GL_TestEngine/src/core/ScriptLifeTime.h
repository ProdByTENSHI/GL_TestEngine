#pragma once

namespace engine {
	// Scripts that need to perform stuff on Start, Update, Render or on Destroy can inherit from this and add themselves to the Call Stack of the the Application
	// The onRender function should

	/* == USAGE ==
	* -- In Script Class Definition -- : class Test : ScriptLifeTime { void onUpdate() { std::cout << "Updating" << std::endl; }
	* -- In Main -- : Application* app = new Application(...); Test test;
	* -- In Main -- : app->addToCallStack(&test);
	*/
	struct ScriptLifeTime {
		virtual void onAppStart() {}
		virtual void onUpdate() {}
		virtual void onRender() {}
	};
}