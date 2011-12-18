#pragma once

#include <iostream>
#include <vector>
#include "Index.h"
#include "EntitySystemInterface.h"

#include <cassert>

#define nullptr 0

namespace Entity
{

template<typename QueryPredicate>
struct View;

class EntitySystem
{

public:
	template <typename... Inputs>
	EntitySystem(Index<Inputs...> index);
	

	template<typename SystemType>
	typename SystemType::Component* 
	get(int _entity, SystemType* unused=0);
	
	template<typename SystemType>
	void set(int _entity, typename SystemType::Component* component);

	template<typename SystemType>
	bool has(int _entity, SystemType* unused=0) const;

	void add(int amount);

	/*template<typename PredicateQuery>
	Entity::View<PredicateQuery> query() 
	{
		Entity::View<PredicateQuery> q;
		subscribe(&q);
		return q; 
	}*/

	void subscribe(Entity::ComponentSubscriber* s)
	{
		m_subscribers.push_back(s);
	}
	int size() { return m_count; } 
	//template<typename... Query>
	//View view() const;

private:
	int m_count;
	const int m_num_systems;
	std::vector<Entity::ComponentSubscriber*> m_subscribers;

	std::vector<void*>* m_component_data;
};

template <typename... Inputs>
EntitySystem::EntitySystem(Index<Inputs...> index)
	: m_num_systems(sizeof...(Inputs))
	, m_count(0)
{
	index.init();
	m_component_data = new std::vector<void*>[m_num_systems];
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
	if(m_component_data[Index<SystemType>::index][_entity] != nullptr)
	{
		delete static_cast<typename SystemType::Component*>(
			m_component_data[Index<SystemType>::index][_entity]);
	}
	m_component_data[Index<SystemType>::index][_entity] = component;
}

template<typename SystemType>
bool
EntitySystem::has(int _entity, SystemType* unused) const
{
	assert(0 <= Index<SystemType>::index);
	assert(_entity < m_count);
	return m_component_data[Index<SystemType>::index][_entity] != nullptr;
}

}//namespace
