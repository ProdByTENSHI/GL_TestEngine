#include "ContainerUtility.h"

namespace utility {
	static ContainerUtility* instance = nullptr;

	ContainerUtility::ContainerUtility() { }

	ContainerUtility* ContainerUtility::getInstance() {
		if (instance == nullptr)
			instance = new ContainerUtility();

		return instance;
	}
}