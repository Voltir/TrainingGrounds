#pragma once
#include <iostream>
#include <functional>
#include <boost/iterator/iterator_facade.hpp>
//#include "EntitySystemInterface.h"

#include "Eid.h"
#include "Definition.h"
//#include "QueryPredicates.h"
#include "Table.h"

#include <set>

namespace Entity
{


//class EntitySystem;

/*
class ViewIterator
	: public boost::iterator_facade<
		  ViewIterator
		, int
		, boost::forward_traversal_tag
		, int
	 >
{
public:
	ViewIterator() 
		: m_count(0) {}

	ViewIterator(int count) 
		: m_count(count) {}

private:
	int m_count;
	friend class boost::iterator_core_access;

	void increment() { m_count += 1; }

	bool equal(ViewIterator const& other) const { return m_count == other.m_count; }

	int dereference() const { return m_count; }
};
*/

template<typename tag, typename QueryPredicate>
class View //: public ComponentSubscriber
{
public:
	View(Table<tag>* table);

	template <typename ComponentType>
	std::function<void(eid<tag> e,ComponentType* c)>
	makeSetHook(ComponentType* unused = NULL);

	void check(eid<tag> e);
	
	typename std::set<eid<tag>>::iterator begin() { return m_eids.begin(); }
	typename std::set<eid<tag>>::iterator end() { return m_eids.end(); }


private:
	Table<tag>* m_table;
	std::set<eid<tag>> m_eids;
};

template<typename tag, typename QueryPredicate>
View<tag,QueryPredicate>::View(Table<tag>* table)
	: m_table(table)
{
	QueryPredicate::registerSetHook(
		m_table,const_cast<View<tag,QueryPredicate>*>(this));

	for(auto e : *table)
	{
		check(e);
	}
}

template<typename tag, typename QueryPredicate>
void
View<tag,QueryPredicate>::check(eid<tag> e)
{
	using namespace std;

	cout << "checking " 
		<< e
		<< " -- " 
		<< QueryPredicate::evaluate(m_table,e) 
		<< endl;

	/* We should not modify (erase or insert) the eids set here
	 * as this gets called between a begin/end over that set
	 * I am thinking a difference set should be saved and applied
	 * whenever begin is called.
	 */
	if(QueryPredicate::evaluate(m_table,e) == false)
	{
		cout << "EVAL FALSE!" << endl;
		auto it = m_eids.find(e);
		if(it != m_eids.end())
		{
			m_eids.erase(it);
		}
	}
	else 
	{
		cout << "EVAL TRUE!" << endl;
		m_eids.insert(e);
	}
}

template<typename tag, typename QueryPredicate>
template<typename ComponentType>
std::function<void(eid<tag> e, ComponentType* c)>
View<tag,QueryPredicate>::makeSetHook(ComponentType* unused)
{
	return [this](eid<tag> e, ComponentType* c) { this->check(e); };
}

} //namespace Entity
