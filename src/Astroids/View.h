#pragma once
#include <boost/iterator/iterator_facade.hpp>

#include "EntitySystemInterface.h"

namespace Entity
{

template<typename QueryPredicate>
class View : public ComponentSubscriber
{
public:
	static int size() { return m_size; }
	virtual void publish() { m_size += 1; }

private:
	static int m_size;
};


template<typename QueryPredicate>
int View<QueryPredicate>::m_size = 0;




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

/*class View
{
public:
	//void add();
	//void remove();

	ViewIterator begin() { return ViewIterator(); }
	ViewIterator end() { return ViewIterator(10); }
private:
};*/

} //namespace Entity
