#include "ContainerUtility.h"

// TODO: Move this to Header File
namespace engine {
	static ContainerUtility* instance = nullptr;

	ContainerUtility::ContainerUtility() { }

	ContainerUtility* ContainerUtility::getInstance() {
		if (instance == nullptr)
			instance = new ContainerUtility();

		return instance;
	}
}