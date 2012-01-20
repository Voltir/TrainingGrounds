#pragma once

#include "Eid.h"
#include "ComponentStore.h"

namespace Entity
{

template<typename tag, typename ComponentT>
struct Index
{
	static int index;
};

template<typename tag, typename ComponentT>
int Index<tag,ComponentT>::index = -1;


//Definitions allow EntitySystem to access ComponentStores by type
template <typename ComponentT> struct _dense;
template <typename ComponentT> struct _sparse;

template <typename... ListT> struct Definition;

template <typename tag, typename HeadT, typename... TailT> 
struct Definition<tag, HeadT, TailT...>
{
	//as in python, "__" means private but not really.
	void __generate(std::vector<ComponentStore*>& store)
	{
		Definition<tag,HeadT> head;
		head.__generate(store);
		Definition<tag,TailT...> rest;
		rest.__generate(store);
	};
};

template <typename tag, typename ComponentT>
struct Definition<tag, _dense<ComponentT>>
{
	void __generate(std::vector<ComponentStore*>& store)
	{
		store.push_back(new DenseComponentStore<tag,ComponentT>());
		Index<tag,ComponentT>::index = store.size() - 1;
	}
};

template <typename tag, typename ComponentT>
struct Definition<tag, _sparse<ComponentT>>
{
	void __generate(std::vector<void*>& store)
	{
		store.push_back(new SparseComponentStore<tag,ComponentT>());
		Index<tag,ComponentT>::index = store.size() - 1;
	}
};

/*
template <typename tag, typename ComponentT> struct Xyzzy
{
	
	static ComponentStore<tag, ComponentT>* magic;

	static bool used;

	static ComponentT* get(const eid<tag>& e) 
	{ 
		return magic->get(e); 
	}

	static void set(const eid<tag>& e, ComponentT* component) 
	{ 
		magic->set(e,component); 
	}
	static bool has(const eid<tag>& e) 
	{ 
		return magic->has(e); 
	}
};

template<typename tag,typename ComponentT>
ComponentStore<tag,ComponentT>* Xyzzy<tag,ComponentT>::magic = 0;

template<typename tag,typename ComponentT>
bool Xyzzy<tag,ComponentT>::used = false;


template <typename tag, typename ComponentT>
struct Definition<tag, _dense<ComponentT>>
{
	struct Check
	{
		static_assert(Xyzzy<tag,ComponentT>::used == false,"Please do not instantiate multiple tables with the same tag");
	 	//typename Xyzzy<tag,ComponentT>::used = true;
		Xyzzy<tag,ComponentT>::used = true;
	};
	
	void __generate()
	{
		Xyzzy<tag,ComponentT>::magic = new DenseComponentStore<tag,ComponentT>;
	}
};

template <typename tag, typename ComponentT>
struct Definition<tag, _sparse<ComponentT>>
{
	void __generate()
	{
		Xyzzy<tag,ComponentT>::magic = new SparseComponentStore<tag,ComponentT>;
	}
};
*/
}//namespace
