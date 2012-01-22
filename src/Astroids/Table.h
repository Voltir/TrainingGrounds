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

	template<typename ComponentType>
	void 
	registerSetHook(std::function<void(eid<tag> e, ComponentType* c)> fn);

	/*
	template<typename ComponentType>
	void 
	hookGet(std::function<void(eid<tag> e)> fn);
	*/

	//void hookHas?
	//void hookCreate?

	/*
	//size doesnt make sense. Could we do something else?
	//int size() const { return m_size; } 
	*/

private:
	std::vector<ComponentStore*> m_store;
};


#include "TableImpl.h"	
}//namespace
