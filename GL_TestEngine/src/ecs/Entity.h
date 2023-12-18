#pragma once

#include <iostream>

namespace ecs {
	class Entity {
	public:
		// Spawn Entity only through EntityManager to prevent ID overlap issues
		Entity(unsigned int id);

		// Make sure to only copy attributes but not the ID
		// TODO: Implement this once Entity Class is setup
		Entity(const Entity& other);

	private:
		unsigned int m_id = 0;
	};
}