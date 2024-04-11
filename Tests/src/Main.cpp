#include "core/Application.h"

int main(int argc, char* argv[]) {
	engine::Application* app = new engine::Application("TEST", 1000, 1000);
	app->update();

	delete app;

	return 0;
}