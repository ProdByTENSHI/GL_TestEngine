#include "core/GameManager.h"

int main(int argc, char* argv[]) {
	engine::GameManager* manager = new engine::GameManager();
	manager->update();

	delete manager;

	return 0;
}