#include "ECS.h"

#include <iostream>
#include <string>
#include <algorithm>

#include "logger/Logger.h"
#include "utility/ContainerUtility.h"
#include "utility/Bit.h"
#include "TransformComponent.h"

namespace engine {
#pragma region Entity Manager
	static EntityManager* instance = nullptr;

	EntityManager::EntityManager() {
		std::vector<BaseComponent*> v;
		m_defaultGroup = createEntityGroup(v);
	}

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
#pragma endregion

#pragma region Entity
	Entity& EntityManager::createEmptyEntity() {
		Entity* entity = new Entity(m_entityCount);
		entity->group = m_defaultGroup;

		std::cout << "Created Entity with the ID " << entity->getId() << " : " << entity << std::endl;

		moveEntityToGroup(*entity, *m_defaultGroup);

		m_entityCount++;
		return *entity;
	}

	Entity* EntityManager::getEntityById(unsigned int id) {
		if (id > m_entityCount) {
			std::cout << "No Entity with the ID " << id << " was found" << std::endl;
			return nullptr;
		}

		for (unsigned int group = 0; group < m_groupCount; group++) {
			for (unsigned int chunk = 0; chunk < m_entityGroups[group]->chunks.size(); chunk++) {
				unsigned int entityArrayLength = (sizeof(m_entityGroups[group]->chunks[chunk]->entities) / sizeof(m_entityGroups[group]->chunks[chunk]->entities[0]));
				for (int entity = 0; entity < entityArrayLength; entity++) {
					if (m_entityGroups[group]->chunks[chunk]->entities[entity] == nullptr)
						break;

					if (m_entityGroups[group]->chunks[chunk]->entities[entity]->getId() == id)
						return m_entityGroups[group]->chunks[chunk]->entities[entity];
				}
			}
		}

		std::cout << "Could not find Entity with the ID " << id << std::endl;
		return nullptr;
	}

#pragma endregion

#pragma region Component
	BaseComponent* EntityManager::addComponent(Entity& entity, BaseComponent* component) {
		std::vector<BaseComponent*>& components = getEntityComponents(entity);
		if (component->getType() & ComponentType::InvalidComponent) {
			std::cout << "Component " << component->getName() << " cannot be added to Entity " << entity.getId() << " as it is not valid" << std::endl;
			return nullptr;
		}

		// Make sure that the Component is not already on the Entity if it is Unique
		if (component->isComponentUnique() && std::find(components.begin(), components.end(), component) != components.end()) {
			std::cout << "Component " << component->getName() << " cannot be added to Entity " << entity.getId() << " twice as it is unique" << std::endl;
			return nullptr;
		}

		// TODO: Remove this ugly fucking casting shit and figure out a different way
		// Add to the fitting Registry
		UpdateComponent* updateComp = dynamic_cast<UpdateComponent*>(component);
		if (updateComp != nullptr)
			m_updateRegistry.push_back(updateComp);
		else
			delete updateComp;

		RenderComponent* renderComp = dynamic_cast<RenderComponent*>(component);
		if (renderComp != nullptr)
			m_renderRegistry.push_back(renderComp);
		else
			delete renderComp;

		// Insert Components into m_entityComponents Vector
		components.push_back(component);

		// Find Group or Create a new one based on the updated Components
		moveEntityToGroup(entity, getGroupByComponents(components));

		component->onAdd();

		return component;
	}

	BaseComponent* EntityManager::addComponent(unsigned int entityID, BaseComponent* component) {
		Entity* entity = getEntityById(entityID);
		if (entity == nullptr)
			return nullptr;

		addComponent(*entity, component);
		return component;
	}

	// TODO: Refactor Component Type Casting into function
	void EntityManager::removeComponent(Entity& entity, BaseComponent& component) {
		// Remove Component from Registries
		UpdateComponent* updateComp = dynamic_cast<UpdateComponent*>(&component);
		if (updateComp != nullptr) {
			removeComponentFromRegistry<UpdateComponent>(*updateComp, m_updateRegistry);
			std::cout << "Removed " << component.getName() << " from the Update Registry" << std::endl;
		}
		else {
			delete updateComp;
		}

		RenderComponent* renderComp = dynamic_cast<RenderComponent*>(&component);
		if (renderComp != nullptr) {
			removeComponentFromRegistry<RenderComponent>(*renderComp, m_renderRegistry);
			std::cout << "Removed " << component.getName() << " from the Render Registry" << std::endl;
		}
		else {
			delete renderComp;
		}

		component.onRemove();

		// Remove Component from the Entity-Components Vector
		for (unsigned int i = 0; i < m_entityComponents[entity.getId()].size(); i++) {
			if (*m_entityComponents[entity.getId()][i] != component)
				continue;

			m_entityComponents[entity.getId()].erase(m_entityComponents[entity.getId()].begin() + i);
			break;
		}
	}

	void EntityManager::printComponents(const Entity& entity) {
		std::vector<BaseComponent*>& components = getEntityComponents(entity);

		std::cout << "<=== ENTITY " << entity.getId() << " ===>" << std::endl;
		std::cout << "\t" << "Entity Group: " << entity.group->id << " : " << entity.group << std::endl;
		for (unsigned int i = 0; i < components.size(); i++) {
			std::cout << "\tComponent: " << i << '\t' << components[i]->getName() << " : " << &components[i] << std::endl;
		}

		std::cout << std::endl;
	}

	// TODO: Return Array of Component if more than one of that type are attached to the Entity
	BaseComponent* EntityManager::getComponentByType(const Entity& entity, ComponentType type) {
		std::vector<BaseComponent*>& components = getEntityComponents(entity);
		if (type & ComponentType::InvalidComponent) {
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
	EntityGroup* EntityManager::createEntityGroup(std::vector<BaseComponent*> components) {
		unsigned int componentSize = (unsigned int)(sizeof(components) / sizeof(components[0]));

		EntityGroup* group = new EntityGroup();
		group->id = m_groupCount;
		group->components = components;
		m_entityGroups.push_back(group);

		std::cout << "<===================================>" << std::endl;
		std::cout << "Created Group " << group->id << " : " << group << std::endl;
		std::cout << "\tGroup created with " << components.size() << " Components" << std::endl;
		for (const auto& c : components) {
			std::cout << "\t" << c->getName() << std::endl;
		}

		// Create first Chunk
		GroupChunk* chunk = createChunk(*group);

		m_groupCount++;
		return group;
	}

	void EntityManager::deleteEntityGroup(EntityGroup& group) {
		for (unsigned int i = 0; i < group.chunks.size(); i++) {
			removeChunk(group, i);
		}

		std::cout << "Deleted Group " << group.id << std::endl;

		delete& group;
	}

	void EntityManager::moveEntityToGroup(Entity& entity, EntityGroup& group) {
		unsigned int groupEntityCounter = 0;

		// Remove from old Group(Dont look at the nested for-loops pls)
		for (unsigned int i = 0; i < entity.group->chunks.size(); i++) {
			unsigned int entitySize = (unsigned int)(sizeof(entity.group->chunks[i]->entities) / sizeof(entity.group->chunks[i]->entities[0]));
			for (unsigned int e = 0; e < entitySize; e++) {
				if (entity.group->chunks[i]->entities[e] == &entity)
					entity.group->chunks[i]->entities[e] = nullptr;

				if (entity.group->chunks[i]->entities[e] != nullptr)
					groupEntityCounter++;
			}
		}

		// Add To Group
		GroupChunk* chunk = new GroupChunk{ group };
		int slot = getFreeChunkSlot(*group.chunks[group.chunks.size() - 1]);

		// Create Chunk if the Group doesn't have one or the last chunk is full
		if (group.chunks.size() == 0 || slot == -1) {
			chunk = createChunk(group);
			chunk->entities[0] = &entity;	// Insert Entity into the first Slot since after creation this will be the 
			return;
		}

		chunk = group.chunks[group.chunks.size() - 1];
		chunk->entities[slot] = &entity;

		// Set Group of Entity to this
		entity.group = &group;

		// Delete old Group if it doesn't have anymore Entities
		if (groupEntityCounter == 0 && entity.group->id != group.id)
			deleteEntityGroup(*entity.group);

		std::cout << "Moved Entity " << entity.getId() << " to Group " << group.id << std::endl;
	}

	EntityGroup& EntityManager::getGroupByComponents(std::vector<BaseComponent*>& components) {
		if (components.size() == 0)
			return *m_defaultGroup;

		EntityGroup* entityGroup = nullptr;

		// Iterate through Groups and check if the Components are the same(Component Order does not matter because of Vector Comparison Implementation -> See ContainerUtility.cpp)
		for (EntityGroup* group : m_entityGroups) {
			if (ContainerUtility::getInstance()->isVectorEqual(group->components, components))
				return *group;
		}

		// Create new Group if non was found with the given components
		entityGroup = createEntityGroup(components);

		return *entityGroup;
	}

	GroupChunk* EntityManager::createChunk(EntityGroup& group) {
		GroupChunk* chunk = new GroupChunk{ group };
		chunk->id = group.chunks.size();

		group.chunks.push_back(chunk);
		std::cout << "Created Chunk " << chunk->id << " : " << chunk << " for Group " << group.id << std::endl;

		return chunk;
	}

	void EntityManager::removeChunk(EntityGroup& group, unsigned int id) {
		GroupChunk* chunk = getChunk(group, id);
		if (chunk == nullptr)
			return;

		// Delete all Entities from the Chunk
		unsigned int entitySize = (sizeof(chunk->entities) / sizeof(chunk->entities[0]));
		for (unsigned int i = 0; i < entitySize; i++) {
			if (chunk->entities[i] == nullptr)
				continue;

			std::cout << "Deleted Entity " << chunk->entities[i] << " from the Chunk " << chunk << std::endl;
			delete chunk->entities[i];
		}

		// Remove Chunks from group.chunks Vector
		group.chunks.erase(group.chunks.begin() + id);

		std::cout << "Removed Chunk " << id << " from the Group " << group.id << " : " << chunk << std::endl;

		delete chunk;
	}

	GroupChunk* EntityManager::getChunk(EntityGroup& group, unsigned int id) {
		if (id > group.chunks.size()) {
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

#pragma region Registry
	// TODO: Refactor Component Casting
	// TODO: Fix Texture not being unbound after usage leading to the texture being applied to all Entities if they dont have their own Texture
	// TODO: Actually use the fucking Registers
	void EntityManager::update(Shader& shader) {
		shader.bind();

		for (auto& ec : m_entityComponents) {
			// Update Components
			for (auto& updateComponent : ec.second) {
				UpdateComponent* update = dynamic_cast<UpdateComponent*>(updateComponent);
				if (update == nullptr)
					continue;

				update->update(shader);
				updateComponent->setShaderUniforms(shader);
			}
		}

		shader.unbind();
	}

	void EntityManager::render(Shader& shader) {
		shader.bind();

		for (auto& ec : m_entityComponents) {
			// Render Components
			for (auto& renderComponent : ec.second) {
				RenderComponent* render = dynamic_cast<RenderComponent*>(renderComponent);
				if (render == nullptr)
					continue;

				renderComponent->setShaderUniforms(shader);
				render->render(shader);
			}
		}

		shader.unbind();
	}
#pragma endregion
}