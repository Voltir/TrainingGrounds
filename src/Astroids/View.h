#pragma once
#include <boost/iterator/iterator_facade.hpp>
#include "EntitySystemInterface.h"
#include "QueryPredicates.h"

namespace Entity
{

class EntitySystem;

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

template<typename QueryPredicate>
class View : public ComponentSubscriber
{
friend class EntitySystem;

public:
	View(const EntitySystem* es);

	int size() { return m_size; }

	virtual void publish() { m_size += 1; }
	
	ViewIterator begin() { return ViewIterator(0); }
	ViewIterator end() { return ViewIterator(m_size); }

private:
	const EntitySystem* m_es;
	int m_size;
};

template<typename QueryPredicate>
View<QueryPredicate>::View(const EntitySystem* es)
	: m_es(es)
{
	m_size = 0;
	//for(int i=0; i<es->size();++i)
	//{
	//	if(QueryPredicate::evaluate(es,i))
	//		m_size += 1;
	//}
}

} //namespace Entity
