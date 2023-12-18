#include "EntityManager.h"

namespace ecs {
	static EntityManager* instance = nullptr;

	EntityManager* EntityManager::getInstance() {
		if (instance == nullptr)
			instance = new EntityManager();

		return instance;
	}

	Entity* EntityManager::spawnEmpty() {
		++m_entityCount;
	}
}