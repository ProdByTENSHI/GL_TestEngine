#include "ECS.h"

#include <iostream>
#include <string>
#include <algorithm>

#include "logger/Logger.h"
#include "utility/ContainerUtility.h"

namespace ecs {
#pragma region Entity Manager
	static EntityManager* instance = nullptr;

	EntityManager::EntityManager() {
		std::vector<BaseComponent> v;
		m_defaultGroup = createEntityGroup(v);
	}

	EntityManager::~EntityManager() {
		// Delete all Entities and free up all resources
		for (EntityGroup* group : m_entityGroups) {
			deleteEntityGroup(*group);				// Fick dich doch das klappt noch nicht wegen dem Vector Scheiß
		}
	}

	EntityManager* EntityManager::getInstance() {
		if (instance == nullptr)
			instance = new EntityManager();

		return instance;
	}
#pragma endregion

#pragma region Entity
	Entity* EntityManager::createEmptyEntity() {
		Entity* entity = new Entity(m_entityCount);
		addEntityToGroup(entity, *m_defaultGroup);

		//logger::Logger::getInstance()->write(std::string("Created Entity"));
		std::cout << "Created Entity with the ID " << entity->getId() << std::endl;

		m_entityCount++;
		return entity;
	}

	Entity* EntityManager::getEntityById(unsigned int id) {
		if (id > m_entityCount) {
			std::cout << "No Entity with the ID " << id << " was found" << std::endl;
			return nullptr;
		}

		// If this does not work run through each Group and Chunk to find the Entity
		for (int group = 0; group < m_groupCount; group++) {
			for (int chunk = 0; chunk < m_entityGroups[group]->chunks.size(); chunk++) {
				unsigned int entityArrayLength = (sizeof(m_entityGroups[group]->chunks[chunk]->entities) / sizeof(m_entityGroups[group]->chunks[chunk]->entities[0]));
				for (int entity = 0; entity < entityArrayLength; entity++) {
					if (m_entityGroups[group]->chunks[chunk]->entities[entity] == nullptr)
						break;

					if (m_entityGroups[group]->chunks[chunk]->entities[entity]->getId() == id)
						return m_entityGroups[group]->chunks[chunk]->entities[entity];
				}
			}
		}

		return nullptr;
	}

#pragma endregion

#pragma region Component
	void EntityManager::addComponent(const Entity& entity, BaseComponent* component) {
		std::vector<BaseComponent*>& components = getEntityComponents(entity);
		if (component->getType() == ComponentType::None) {
			std::cout << "Component " << component->getName() << " cannot be added to Entity " << entity.getId() << " as it is not valid" << std::endl;
			return;
		}

		// Make sure that the Component is not already on the Entity if it is Unique
		if (component->isComponentUnique() && std::find(components.begin(), components.end(), component) != components.end()) {
			std::cout << "Component " << component->getName() << " cannot be added to Entity " << entity.getId() << " twice as it is unique" << std::endl;
			return;
		}

		std::cout << "Added " << component->getName() << " : " << component << " : " << " to Entity " << entity.getId() << std::endl;

		// Insert Components into m_entityComponents Vector
		components.push_back(component);
	}

	void EntityManager::addComponent(unsigned int entityID, BaseComponent* component) {
		const Entity* entity = getEntityById(entityID);
		addComponent(*entity, component);
	}

	void EntityManager::printComponents(const Entity& entity) {
		std::vector<BaseComponent*>& components = getEntityComponents(entity);

		std::cout << "<=== ENTITY " << entity.getId() << " ===>" << std::endl;
		for (unsigned int i = 0; i < components.size(); i++) {
			std::cout << "\tComponent: " << i << '\t' << components[i]->getName() << " : " << &components[i] << std::endl;
		}

		std::cout << std::endl;
	}

	BaseComponent* EntityManager::getComponentByType(const Entity& entity, ComponentType type) {
		std::vector<BaseComponent*>& components = getEntityComponents(entity);
		if (type == ComponentType::None) {
			std::cout << "Cannot get Invalid Component from Entity " << entity.getId() << std::endl;
			return nullptr;
		}

		for (unsigned int i = 0; i < components.size(); i++) {
			if (components[i]->getType() == type)
				return components[i];
		}

		return nullptr;
	}

	std::vector<BaseComponent*>& EntityManager::getEntityComponents(const Entity& entity) {
		return m_entityComponents[entity.getId()];
	}
#pragma endregion

#pragma region Entity Group & Chunk Management
	EntityGroup* EntityManager::createEntityGroup(std::vector<BaseComponent> components) {
		unsigned int componentSize = (unsigned int)(sizeof(components) / sizeof(components[0]));

		EntityGroup* group = new EntityGroup();
		group->id = m_groupCount;
		group->components = components;
		m_entityGroups.push_back(group);

		// Create first Chunk
		GroupChunk* chunk = createChunk(*group);

		m_groupCount++;
		return group;
	}

	// TODO: Fix Out Of Bounds Error -> When deleting a Chunk it gets popped of the Vector and therefore the Size and ID of the other Elements change
	void EntityManager::deleteEntityGroup(EntityGroup& group) {
		for (auto& chunk : group.chunks) {
			removeChunk(group, chunk->id);
		}

		//logger::Logger::getInstance()->write("Deleted Group with the ID " + group.id);
		std::cout << "Deleted Entity Group with the ID: " << group.id << std::endl;
	}

	void EntityManager::addEntityToGroup(Entity* entity, EntityGroup& group) {
		GroupChunk* chunk = new GroupChunk{ group };
		int slot = getFreeChunkSlot(*group.chunks[group.chunks.size() - 1]);

		// Create Chunk if the Group doesn't have one or the last chunk is full
		if (group.chunks.size() == 0 || slot == -1) {
			chunk = createChunk(group);
			chunk->entities[0] = entity;	// Insert Entity into the first Slot since after creation this will be the 
			return;
		}

		chunk = group.chunks[group.chunks.size() - 1];
		chunk->entities[slot] = entity;
	}

	void EntityManager::removeEntityFromGroup(Entity* entity, EntityGroup& group) {
		// Go through each Chunk and look for Entity 
		//logger::Logger::getInstance()->write(std::string("Removed Entity with the ID " + entity->getId()) + std::string(" from the Group " + group.id));
	}

	EntityGroup& EntityManager::getGroupByComponents(std::vector<BaseComponent>& components) {
		if (components.size() == 0)
			return *m_defaultGroup;

		EntityGroup* entityGroup;

		// Iterate through Groups and check if the Components are the same(Component Order does not matter because of Vector Comparison Implementation -> See ContainerUtility.cpp)
		for (EntityGroup* group : m_entityGroups) {
			if (!utility::ContainerUtility::getInstance()->isVectorEqual(group->components, components))
				continue;

			entityGroup = group;
			break;
		}

		// Create new Group if non was found with the given components
		entityGroup = createEntityGroup(components);

		return *entityGroup;
	}

	GroupChunk* EntityManager::createChunk(EntityGroup& group) {
		GroupChunk* chunk = new GroupChunk{ group };
		chunk->id = group.chunks.size();

		group.chunks.push_back(chunk);
		std::cout << "Created Chunk " << chunk->id << " with the Memory Adress: " << chunk << std::endl;

		//logger::Logger::getInstance()->write("Created new Chunk");
		std::cout << "Created new Chunk with the ID " << chunk->id << " for the Group " << group.id << std::endl;
		return chunk;
	}

	void EntityManager::removeChunk(EntityGroup& group, unsigned int id) {
		GroupChunk* chunk = getChunk(group, id);
		if (chunk == nullptr)
			return;

		// Delete all Entities from the Chunk
		unsigned int entitySize = (sizeof(chunk->entities) / sizeof(chunk->entities[0]));
		for (unsigned int i = 0; i < entitySize; i++) {
			std::cout << "Removed Entity : " << i << " : " << chunk->entities[i] << std::endl;
			delete chunk->entities[i];
		}

		// Remove Chunks from group.chunks Vector
		group.chunks.erase(group.chunks.begin() + id);

		//logger::Logger::getInstance()->write("Removed Chunk ");
		std::cout << "Removed Chunk " << id << " from the Group " << group.id << " : " << chunk << std::endl;

		delete chunk;
	}

	GroupChunk* EntityManager::getChunk(EntityGroup& group, unsigned int id) {
		if (id > group.chunks.size()) {
			//logger::Logger::getInstance()->write("Chunk does not exist. ID: ");
			std::cout << "Chunk with the ID: " << id << " does not exist in Group " << group.id << std::endl;
			return nullptr;
		}

		return group.chunks[id];
	}

	const int EntityManager::getFreeChunkSlot(const GroupChunk& chunk) {
		const unsigned int arrayLength = (sizeof(chunk.entities) / sizeof(chunk.entities[0]));

		for (unsigned int i = 0; i < arrayLength; i++) {
			if (chunk.entities[i] == nullptr)
				return i;
		}

		return -1;
	}
#pragma endregion
}