#pragma once

#include <vector>

#include "Definition.h"
#include "ComponentStore.h"
#include "Eid.h"

#define nullptr 0

namespace Entity
{

template<typename tag>
class Table
{

public:
	
	template <typename... Inputs>
	Table(Definition<tag,Inputs...> def);

	~Table();

	void create(int amount);
	//void destroy(eid)
	
	template<typename ComponentType>
	ComponentType*
	get(eid<tag> id, ComponentType* unused=0);

	template<typename ComponentType>
	void 
	set(eid<tag> id, ComponentType* component);
	
	template<typename ComponentType>
	bool 
	has(eid<tag> id, ComponentType* unused=0) const;

	/*
	//void subscribe(Entity::ComponentSubscriber* s);

	//size doesnt make sense. Could we do something else?
	//int size() const { return m_size; } 
	*/

private:
	std::vector<void*> m_store;
};


#include "TableImpl.h"	
}//namespace
