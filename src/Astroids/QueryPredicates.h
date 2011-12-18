#pragma once

namespace Entity
{

class EntitySystem;

/*
template <typename SystemType>
struct _has
{
	static bool evaluate(const EntitySystem* es, int eid)
	{
		return es->has<SystemType>(eid);
	}
};
template <typename PredicateType>
struct _not
{
	static bool evaluate(const EntitySystem* es, int eid)
	{
		return !PredicateType::evaluate(es,eid);
	}
};

template <typename... Inputs>
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
