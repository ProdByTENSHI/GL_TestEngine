#include "core/GameManager.h"

#include <iostream>

int main(int argc, char* argv[]) {
	core::GameManager* manager = new core::GameManager();
	manager->update();

	delete manager;

	return 0;
}