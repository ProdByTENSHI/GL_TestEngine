#include "core/GameManager.h"

#include <iostream>

int main(int argc, char* argv[]) {
	engine::GameManager* manager = new engine::GameManager();
	manager->update();

	delete manager;

	return 0;
}