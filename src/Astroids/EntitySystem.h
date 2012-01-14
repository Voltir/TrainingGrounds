#pragma once

#include <iostream>
#include <vector>
#include <cassert>

#include "Index.h"
#include "EntitySystemInterface.h"

#define nullptr 0

namespace Entity
{

class EntitySystem
{

public:
	template <typename... Inputs>
	EntitySystem(Index<Inputs...> index);
	
	void create(int amount);

	template<typename ComponentType>
	ComponentType*
	get(int _entity, ComponentType* unused=0);
	
	template<typename ComponentType>
	void set(int _entity, ComponentType* component);

	template<typename ComponentType>
	bool has(int _entity, ComponentType* unused=0) const;

	void subscribe(Entity::ComponentSubscriber* s);

	//size doesnt make sense. Could we do something else?
	int size() const { return m_size; } 

private:
	int m_size;
	int m_num_systems;
	std::vector<ComponentSubscriber*> m_subscribers;
	std::vector<void*>* m_component_data;
};

template <typename... Inputs>
EntitySystem::EntitySystem(Index<Inputs...> index)
	: m_num_systems(sizeof...(Inputs))
	, m_size(0)
{
	index.init();
	m_component_data = new std::vector<void*>[m_num_systems];

	//Definition<Inputs...>::allocate(m_dense_data,m_sparse_data);
}
/*
template<typename ComponentType>
ComponentType*
EntitySystem::magic(int _entity, Definition<ComponentType>::Dense* unused)
{
	cout << "Lol get dense" << endl;
}

template<typename ComponentType>
ComponentType*
EntitySystem::magic(int _entity, Definition<ComponentType>::Sparse* unused)
{
	cout << "Lol get sparse" << endl;
}
*/
template<typename ComponentType>
ComponentType*
EntitySystem::get(int _entity, ComponentType* unused)
{
	assert(0 <= Index<ComponentType>::index);
	assert(_entity < m_size);
	return static_cast<ComponentType*>(
		m_component_data[Index<ComponentType>::index][_entity]);
}

template<typename ComponentType>
void
EntitySystem::set(int _entity, ComponentType* component)
{
	assert(0 <= Index<ComponentType>::index);
	assert(_entity < m_size);

	if(m_component_data[Index<ComponentType>::index][_entity] != nullptr)
	{
		delete static_cast<ComponentType*>(
			m_component_data[Index<ComponentType>::index][_entity]);
	}
	m_component_data[Index<ComponentType>::index][_entity] = component;

	for(auto subscriber: m_subscribers)
	{
		subscriber->publishAfterAdd(_entity);
	}
}

template<typename ComponentType>
bool
EntitySystem::has(int _entity, ComponentType* unused) const
{
	assert(0 <= Index<ComponentType>::index);
	assert(_entity < m_size);
	return m_component_data[Index<ComponentType>::index][_entity] != nullptr;
}
	
}//namespace
