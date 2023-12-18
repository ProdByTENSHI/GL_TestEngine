#pragma once

#include <unordered_map>

#include "Entity.h"

namespace ecs {
	class EntityManager {
	public:
		static EntityManager* getInstance();

		// Spawns in an Empty Entity
		Entity* spawnEmpty();

	private:
		EntityManager();
		EntityManager(const EntityManager& other);

		// Counter that keeps track of the Entities in the Scene 
		unsigned int m_entityCount;

		// TODO: Create a Pool of IDs that can be used and freed instead of linear IDs that are given by the m_entityCount

		// K: ID; V: Pointer to Entity
		std::unordered_map<unsigned int, Entity*> m_entities;
	};
}