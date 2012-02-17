#pragma once

#include "Eid.h"
#include "Definition.h"
#include "Table.h"
#include "View.h"

namespace Entity
{

//class EntitySystem;

//Has Predicate -- this is used to directly wrap a ComponentType
template <typename ComponentType>
struct _has
{
	template<typename tag>
	static bool evaluate(const Table<tag>* table, eid<tag> e)
	{
		return table->has(e,static_cast<ComponentType*>(NULL));
	}

	template <typename tag, typename QueryPredicate>
	static void registerSetHook(
		Table<tag>* table, 
		View<tag,QueryPredicate>* view)
	{
		auto h = view->makeSetHook(static_cast<ComponentType*>(NULL));
		table->registerSetHook<ComponentType>(h);
	}
};

//Not Predicate
template <typename PredicateType>
struct _not
{
	template<typename tag>
	static bool evaluate(const Table<tag>* table, eid<tag> e)
	{
		return !PredicateType::evaluate(table,e);
	}
	
	template <typename tag, typename QueryPredicate>
	static void registerSetHook(
		Table<tag>* table, 
		View<tag,QueryPredicate>* view)
	{
		PredicateType::registerSetHook(table,view);
	}
};

/*
//And Predicate
template <typename... Predicates>
struct _and
{
	static bool evaluate(const EntitySystem* es, int eid) { }
};

template <typename Head, typename... Tail>
struct _and<Head,Tail...>
{
	static bool evaluate(const EntitySystem* es, int eid)
	{
		return Head::evaluate(es,eid) && _and<Tail...>::evaluate(es);
	}
};

template <typename Head>
struct _and<Head>
{
	static bool evaluate(const EntitySystem* es, int eid) 
	{
		return Head::evaluate(es,eid);
	}
};
*/
}//namespace Entity
