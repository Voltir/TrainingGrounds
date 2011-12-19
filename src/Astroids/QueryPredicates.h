#pragma once

namespace Entity
{

class EntitySystem;

//Has Predicate -- this is used to directly wrap a SystemType
template <typename SystemType>
struct _has
{
	static bool evaluate(const EntitySystem* es, int eid)
	{
		return es->has<SystemType>(eid);
	}
};

//Not Predicate
template <typename PredicateType>
struct _not
{
	static bool evaluate(const EntitySystem* es, int eid)
	{
		return !PredicateType::evaluate(es,eid);
	}
};

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

}//namespace Entity
