#pragma once
#include <iostream>
#include <boost/iterator/iterator_facade.hpp>
#include "EntitySystemInterface.h"
#include "QueryPredicates.h"
#include <set>

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
public:
	View(EntitySystem* es);

	virtual void publishAfterCreate(int eid)
	{
		std::cout << "view -- After Create!" << std::endl;
		check(eid);
	}

	virtual void publishAfterAdd(int eid) 
	{
		std::cout << "view -- After Add!" << std::endl;
		check(eid);
	}
	
	virtual void publishAfterRemove(int eid) 
	{
		std::cout << "view -- After Remove!" << std::endl;
		check(eid);
	}

	void check(int eid)
	{
		using namespace std;
		cout << "checking " << eid << " -- " << QueryPredicate::evaluate(m_es,eid) << endl;
		if(QueryPredicate::evaluate(m_es,eid) == false)
		{
			auto it = foo.find(eid);
			if(it != foo.end())
			{
				foo.erase(it);
			}
		}
		else 
		{
			foo.insert(eid);
		}
	}	

	//ViewIterator begin() { std::cout << "Begin!" << std::endl; return ViewIterator(m_start); }
	//ViewIterator end() { return ViewIterator(m_size); }

	std::set<int>::iterator begin() { foo.begin(); }
	std::set<int>::iterator end() { foo.end(); }


private:
	EntitySystem* m_es;
	std::set<int> foo;
};

template<typename QueryPredicate>
View<QueryPredicate>::View(EntitySystem* es)
	: m_es(es)
{
	using namespace std;
	m_es->subscribe(const_cast<View<QueryPredicate>*>(this));

	for(int i=0; i<m_es->size();++i)
	{
		check(i);
	}
}

} //namespace Entity
