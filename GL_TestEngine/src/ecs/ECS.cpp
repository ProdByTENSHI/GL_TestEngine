#include "ECS.h"

#include <string>

#include "logger/Logger.h"

namespace ecs {
	static EntityManager* instance = nullptr;

	EntityManager::EntityManager() { }

	EntityManager* EntityManager::getInstance() {
		if (instance == nullptr)
			instance = new EntityManager();

		return instance;
	}

	Entity* EntityManager::createEmptyEntity() {
		++m_entityCount;
		Entity* entity = new Entity(m_entityCount);

		return entity;
	}

	// <========== ENTITY GROUP AND CHUNK MANAGEMENT ==========>
	unsigned int EntityGroup::m_groupCount = 0;

	EntityGroup& EntityManager::createEntityGroup(BaseComponent components[]) {
		//unsigned int componentSize = (unsigned int)(sizeof(components) / sizeof(BaseComponent)); -> Das ist fürn Arsch weil die Child Klassen eine andere Größe haben. Das muss irgendwie anders gehen
		std::string loggerOutput;

		EntityGroup* group = new EntityGroup();
		group->id = EntityGroup::getGroupCount();

		// TODO: Make sure there are no duplicate types
		//for (unsigned int i = 0; i < componentSize; i++) {
		//	loggerOutput.append(components[i].name);
		//}

		logger::Logger::getInstance()->write("Created Entity Group with Components: " + loggerOutput);
		return *group;
	}

	void EntityManager::deleteEntityGroup(EntityGroup& group) {
		logger::Logger::getInstance()->write("Deleted Group");
	}

	void EntityManager::addEntityToGroup(Entity* entity, EntityGroup& group) {
		if (group.chunks[group.chunks.size() - 1]->emptySlots.size() == 0) {
			GroupChunk* chunk = createChunk(group);
		}
	}

	void EntityManager::removeEntityFromGroup(Entity* entity, EntityGroup& group) {

	}

	Entity* EntityManager::getEntity(unsigned int id, EntityGroup& group) {
		for (const auto& chunk : group.chunks) {
			for (const auto& entity : chunk->entities) {
				if (entity->getId() == id)
					return entity;
			}
		}
	}

	EntityGroup& EntityManager::getGroupByComponents(BaseComponent componentTypes[]) {
		EntityGroup group;
		return group;

		// If no Group was found with the given Component Types create a new EntityGroup and return it
	}

	GroupChunk* EntityManager::createChunk(EntityGroup& group) {
		GroupChunk chunk{ group };
		group.chunks.push_back(&chunk);

		// Marks all Slots as Free
		for (unsigned int i = 0; i < maxEntitiesPerChunk; i++) {
			chunk.emptySlots.push_back(i);
		}

		logger::Logger::getInstance()->write("Created new Chunk for group " + group.id);
		return &chunk;
	}

	void EntityManager::removeChunk(EntityGroup& group, unsigned int id) {
		GroupChunk* chunk = getChunk(group, id);
		for (const auto& entity : chunk->entities) {
			delete entity;
		}

		// TODO: Remove Chunks from group.chunks Vector

		logger::Logger::getInstance()->write("Removed Chunk " + id);
	}

	GroupChunk* EntityManager::getChunk(EntityGroup& group, unsigned int id) {
		if (id > group.chunks.size()) {
			logger::Logger::getInstance()->write("Chunk does not exist. ID: " + id);
			return nullptr;
		}

		return group.chunks[id];
	}

	unsigned int EntityManager::getFreeChunkSlot(const GroupChunk& chunk) {
		for (unsigned int i = 0; i < chunk.emptySlots.size(); i++) {
			return i;
		}

		return 0xFF;
	}
}