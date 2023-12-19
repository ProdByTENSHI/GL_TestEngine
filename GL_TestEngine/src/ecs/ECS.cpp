#include "ECS.h"

#include <string>
#include <iostream>

#include "logger/Logger.h"

namespace ecs {
	static EntityManager* instance = nullptr;

	EntityManager::EntityManager() { }

	EntityManager::~EntityManager() {
		// Delete all Entities and free up all resources
		for (EntityGroup* group : m_entityGroups) {
			deleteEntityGroup(*group);
		}
	}

	EntityManager* EntityManager::getInstance() {
		if (instance == nullptr)
			instance = new EntityManager();

		return instance;
	}

	Entity* EntityManager::createEmptyEntity() {
		++m_entityCount;
		Entity* entity = new Entity(m_entityCount);
		std::vector<BaseComponent> components;
		addEntityToGroup(entity, getGroupByComponents(components));

		logger::Logger::getInstance()->write(std::string("Created Entity. ID: " + m_entityCount));

		return entity;
	}

	// <========== ENTITY GROUP AND CHUNK MANAGEMENT ==========>
	unsigned int EntityGroup::m_groupCount = 0;

	EntityGroup& EntityManager::createEntityGroup(std::vector<BaseComponent> components) {
		//unsigned int componentSize = (unsigned int)(sizeof(components) / sizeof(BaseComponent)); -> Das ist fürn Arsch weil die Child Klassen eine andere Größe haben. Das muss irgendwie anders gehen
		std::string loggerOutput;

		EntityGroup* group = new EntityGroup();
		group->id = EntityGroup::getGroupCount();
		group->components = components;

		//for (const auto& component : components) {
		//	loggerOutput.append(component.name);
		//}

		logger::Logger::getInstance()->write("Created Entity Group with Components: " + loggerOutput);
		return *group;
	}

	void EntityManager::deleteEntityGroup(EntityGroup& group) {
		for (const auto& chunk : group.chunks) {
			removeChunk(group, chunk->id);
		}

		std::vector<EntityGroup*>::iterator it;
		logger::Logger::getInstance()->write("Deleted Group with the ID " + group.id);
	}

	void EntityManager::addEntityToGroup(Entity* entity, EntityGroup& group) {
		if (group.chunks.size() == 0 || getFreeChunkSlot(*group.chunks[group.chunks.size() - 1])) {
			GroupChunk* chunk = createChunk(group);
		}
	}

	void EntityManager::removeEntityFromGroup(Entity* entity, EntityGroup& group) {
		// Go through each Chunk and look for Entity 
		logger::Logger::getInstance()->write(std::string("Removed Entity with the ID " + entity->getId()) + std::string(" from the Group " + group.id));
	}

	Entity* EntityManager::getEntity(unsigned int id, EntityGroup& group) {
		for (const auto& chunk : group.chunks) {
			for (const auto& entity : chunk->entities) {
				if (entity->getId() == id)
					return entity;
			}
		}
	}

	// TODO: Implement this
	EntityGroup& EntityManager::getGroupByComponents(std::vector<BaseComponent> components) {


		EntityGroup group;
		return group;
	}

	GroupChunk* EntityManager::createChunk(EntityGroup& group) {
		GroupChunk chunk{ group };
		group.chunks.push_back(&chunk);

		logger::Logger::getInstance()->write("Created new Chunk for group " + group.id);
		return &chunk;
	}

	void EntityManager::removeChunk(EntityGroup& group, unsigned int id) {
		GroupChunk* chunk = getChunk(group, id);
		for (const auto& entity : chunk->entities) {
			delete entity;
		}

		// Remove Chunks from group.chunks Vector
		group.chunks.erase(group.chunks.begin() + id);

		logger::Logger::getInstance()->write("Removed Chunk " + id);

		delete chunk;
	}

	GroupChunk* EntityManager::getChunk(EntityGroup& group, unsigned int id) {
		if (id > group.chunks.size()) {
			logger::Logger::getInstance()->write("Chunk does not exist. ID: " + id);
			return nullptr;
		}

		return group.chunks[id];
	}

	unsigned int EntityManager::getFreeChunkSlot(GroupChunk chunk) {
		const unsigned int arrayLength = (sizeof(chunk.entities) / sizeof(GroupChunk));

		for (unsigned int i = 0; i < arrayLength; i++) {
			if (chunk.entities[i] == nullptr)
				return i;
		}

		return 0xFF;
	}
}