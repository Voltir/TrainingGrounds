#include <iostream>
#include <vector>
#include "Index.h"

class EntitySystem;
class EntityView;
class Component;
class NullComponent;
class View;

class EntitySystem
{

friend class EntityView;

public:
	template <typename... Inputs>
	EntitySystem(Index<Inputs...> index);
	
	void add(int ammount);

	template<typename SystemType>
	typename SystemType::Component* get(int _entity, SystemType* unused=0);
	
	template<typename SystemType>
	void set(int _entity, typename SystemType::Component* component);

	template<typename SystemType>
	bool has(int _entity, SystemType* unused=0);

	//template<typename... Query>
	//View view() const;

private:
	int m_count;
	const int m_num_systems;

	std::vector<Component*>* m_component_data;
	NullComponent* m_null;
};

template <typename... Inputs>
EntitySystem::EntitySystem(Index<Inputs...> index)
	: m_num_systems(sizeof...(Inputs))
	, m_count(0)
	, m_null(new NullComponent()) 
{
	index.init();
	m_component_data = new std::vector<Component*>[m_num_systems];
}

void
EntitySystem::add(int amount)
{
	m_count += amount;
	for(int i=0; i<m_num_systems; ++i)
	{
		for(int j=0; j<amount; ++j)
		{
			m_component_data[i].push_back(m_null);
		}
	}
}

template<typename SystemType>
typename SystemType::Component*
EntitySystem::get(int _entity, SystemType* unused)
{
	assert(0 <= Index<SystemType>::index);
	assert(_entity < m_count);
	return static_cast<typename SystemType::Component*>(
		m_component_data[Index<SystemType>::index][_entity]);
}

template<typename SystemType>
void
EntitySystem::set(int _entity, typename SystemType::Component* component)
{
	assert(0 <= Index<SystemType>::index);
	assert(_entity < m_count);
	if(m_component_data[Index<SystemType>::index][_entity] != m_null)
	{
		delete m_component_data[Index<SystemType>::index][_entity];
	}
	m_component_data[Index<SystemType>::index][_entity] = component;
}

template<typename SystemType>
bool
EntitySystem::has(int _entity, SystemType* unused)
{
	assert(0 <= Index<SystemType>::index);
	assert(_entity < m_count);
	return m_component_data[Index<SystemType>::index][_entity] != m_null;
}




class EntityView
{
public:
	EntityView(const EntitySystem& es) : m_es(es) {}
	int size() { return m_es.m_count; } 

private:
	const EntitySystem& m_es;
};

EntityView
EntitySystem::view() const
{
	//EntityView result(*this);
	//return std::move<EntityView>(result);
	return EntityView(*this);
};
