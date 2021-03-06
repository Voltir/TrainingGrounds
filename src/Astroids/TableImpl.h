#pragma once

#include "Table.h"
#include "Definition.h"

template<typename tag>
template<typename... Inputs>
Table<tag>::Table(Definition<tag, Inputs...> def)
{
	def.__generate(m_store);
}

template<typename tag>
Table<tag>::~Table()
{
	for(void* cs : m_store)
	{
		delete static_cast<ComponentStore*>(cs);
	}
}

template<typename tag>
void Table<tag>::create(int amount)
{
	for(void* cs : m_store)
	{
		static_cast<ComponentStore*>(cs)->create(amount);
	}

	//Meh -- using a set<int> for now
	int base = m_foo.size();
	for(int i=0; i<amount; ++i)
	{
		m_foo.insert(eid<tag>(base+i));
	}
}

template<typename tag>
template<typename ComponentT>
void 
Table<tag>::set(eid<tag> id, ComponentT* component)
{
	Accessor<tag,ComponentT>* acc = 
		static_cast<Accessor<tag,ComponentT>*>(
			m_store[Index<tag,ComponentT>::index]);
	acc->set(id,component);
}

template<typename tag>
template<typename ComponentT>
ComponentT* 
Table<tag>::get(eid<tag> id, ComponentT* unused)
{
	Accessor<tag,ComponentT>* acc = 
		static_cast<Accessor<tag,ComponentT>*>(
			m_store[Index<tag,ComponentT>::index]);
	return acc->get(id);
}

template<typename tag>
template<typename ComponentT>
bool 
Table<tag>::has(eid<tag> id, ComponentT* unused) const 
{
	const Accessor<tag,ComponentT>* acc = 
		static_cast<Accessor<tag,ComponentT>*>(
			m_store[Index<tag,ComponentT>::index]);
	return acc->has(id);
}

template<typename tag>
template<typename ComponentT>
void 
Table<tag>::registerSetHook(
	std::function<void(eid<tag> e, ComponentT* c)> hook)
{
	Accessor<tag,ComponentT>* acc = 
		static_cast<Accessor<tag,ComponentT>*>(
			m_store[Index<tag,ComponentT>::index]);
	acc->registerSetHook(hook);
}
