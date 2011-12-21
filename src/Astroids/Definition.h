#pragma once

#include "ComponentStore.h"

//Definitions allow EntitySystem to access ComponentStores by type
template <typename ComponentT> struct _dense;
template <typename ComponentT> struct _sparse;

template <typename... ListT> struct Definition;

template <typename HeadT, typename... TailT> 
struct Definition<HeadT,TailT...>
{
	void __generate()
	{
		Definition<HeadT> head;
		head.__generate();
		Definition<TailT...> rest;
		rest.__generate();
	};
};

template <typename ComponentT> struct Definition<ComponentT>
{
	static ComponentStore<ComponentT>* magic;
	static ComponentT* get(int e) { return magic->get(e); }
	static void set(int e, ComponentT* component) { magic->set(e,component); }
	static bool has(int e) { return magic->has(e); }
};

template<typename ComponentT>
ComponentStore<ComponentT>* Definition<ComponentT>::magic = 0;

template <typename ComponentT>
struct Definition<_dense<ComponentT>>
{
	void __generate()
	{
		Definition<ComponentT>::magic = new DenseComponentStore<ComponentT>;
	}
};

template <typename ComponentT>
struct Definition<_sparse<ComponentT>>
{
	void __generate()
	{
		Definition<ComponentT>::magic = new SparseComponentStore<ComponentT>;
	}
};
