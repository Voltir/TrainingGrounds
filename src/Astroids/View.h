#pragma once

#include <boost/iterator/iterator_facade.hpp>

namespace Entity
{

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

class View
{
public:
	//void add();
	//void remove();

	ViewIterator begin() { return ViewIterator(); }
	ViewIterator end() { return ViewIterator(10); }
private:
};

} //namespace Entity
