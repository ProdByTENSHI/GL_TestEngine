#pragma once

#include <vector>

#include "BaseComponent.h"

namespace ecs {
	constexpr unsigned int maxEntitiesPerChunk = 5;		// TODO: Increase Number once everything is setup

	class Entity {
	public:
		// Only create Entities through the Entity Manager
		Entity(unsigned int id) {
			m_id = id;
		}

		inline unsigned int getId() const { return m_id; }

	private:
		// TODO: Find a way to copy the Components, States, etc without copying the Entity ID. Till that restrict Copy Constructor
		Entity(const Entity& other);

		unsigned int m_id;

	};

	// Das muss vorher weil Visual Studio der Nuttensohn sonst rummeckert und die scheiﬂ Structs nicht kennt
	struct EntityGroup;
	struct GroupChunk;

	// Entities are Grouped by Component Types(Unordered)
	// Each Entity Group has Chunks which can store up to maxEntitiesPerChunk Entities
	// If the last Chunk is full a new Chunk will be created
	// When removing Entities and therefore the attached Components, store the empty Chunk Space in a Vector 
	// On new Entity Creation put it there instead of creating new Chunks / Take up new Space
	struct EntityGroup {
		std::vector<GroupChunk*> chunks;
		std::vector<BaseComponent> components;
		unsigned int id;

	private:
		static unsigned int m_groupCount;
	};

	// A Chunk that serves as a Container for Entities that belong to the same Entity Group
	struct GroupChunk {
		EntityGroup& parentGroup;				// A reference to the EntityGroup the Chunk belongs to
		Entity* entities[maxEntitiesPerChunk];	// An Array that holds all Entity Pointer of this Chunk
		unsigned int id;						// Identifier of the Chunk
	};

	class EntityManager {
	public:
		static EntityManager* getInstance();
		~EntityManager();

		Entity* createEmptyEntity();
		
		// Expensive Operation! Use this only once and cache the Result if Possible!
		Entity* getEntityById(unsigned int id);

	private:
		// Singleton Stuff
		EntityManager();
		EntityManager(const EntityManager& other);

		EntityGroup* createEntityGroup(std::vector<BaseComponent> components);
		void deleteEntityGroup(EntityGroup& group);

		// Adds an Entity to a Group and manages the needed Chunks for that
		void addEntityToGroup(Entity* entity, EntityGroup& group);
		void removeEntityFromGroup(Entity* entity, EntityGroup& group);

		EntityGroup& getGroupByComponents(std::vector<BaseComponent>& components);

		GroupChunk* createChunk(EntityGroup& parent);

		// Removes a Group Chunk and all its Entities
		void removeChunk(EntityGroup& group, unsigned int id);

		GroupChunk* getChunk(EntityGroup& group, unsigned int id);

		// Returns the next Free Slot ID or -1 if none was found
		const int getFreeChunkSlot(const GroupChunk& chunk);

		unsigned int m_entityCount = 0;
		unsigned int m_groupCount = 0;

		std::vector<EntityGroup*> m_entityGroups;
		EntityGroup* m_defaultGroup;					// The Default Group does ot have any Components and is used for Componentless Entities
	};
}