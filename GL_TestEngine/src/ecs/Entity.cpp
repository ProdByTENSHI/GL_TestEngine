#include "Entity.h"

namespace ecs {
	Entity::Entity(unsigned int id) {
		m_id = id;
	}

	Entity::Entity(const Entity& other) { }
}