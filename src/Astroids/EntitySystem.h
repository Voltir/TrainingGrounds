#include <map>
#include <vector>

//using ComponentId = int;
typedef int ComponentId;

class EntitySystem;

struct Component 
{
};

class Entity
{
public:
	Entity(EntitySystem* system) : mSystem(system) {}

	template<typename ComponentType> 
	ComponentType* get();

	template<typename ComponentType>
	void add(ComponentType* comp);

	EntitySystem* mSystem;
	std::map<ComponentId, Component*> mComponents;
};

class EntitySystemView : public std::vector<Entity*>
{
public:
	EntitySystemView() : std::vector<Entity*>() {}

	template<typename ComponentType>
	EntitySystemView getWith();

	void registerComponent(const ComponentId id, Entity* e)
	{
		mComponentMap.insert(std::pair<ComponentId,Entity*>(id,e));
	}

	std::multimap<ComponentId,Entity*> mComponentMap;
};

class EntitySystem : public EntitySystemView
{
public:
	EntitySystem(size_t num_entities) 
	{
		for(int i=0; i<num_entities;++i)
		{
			Entity* e = new Entity(const_cast<EntitySystem*>(this));
			push_back(e);
		}
	}

};

template<typename ComponentType>
EntitySystemView EntitySystemView::getWith()
{
	EntitySystemView result;

	auto it_pair = mComponentMap.equal_range(ComponentType::componentId);
	for(auto it = it_pair.first; it != it_pair.second; ++it)
	{
		Entity* e = it->second;
		result.push_back(e);
		for(auto it = e->mComponents.begin(); it != e->mComponents.end(); ++it)
		{
			result.registerComponent(it->first, e);
		}
		
	}

	return result;
}

template<typename ComponentType>
ComponentType* Entity::get()
{
	return static_cast<ComponentType>(mComponents[ComponentType::componentId]);
}

template<typename ComponentType>
void Entity::add(ComponentType* comp)
{
	mComponents.insert(std::pair<ComponentId,Component*>(ComponentType::componentId,comp));
	mSystem->registerComponent(ComponentType::componentId,const_cast<Entity*>(this));
}
