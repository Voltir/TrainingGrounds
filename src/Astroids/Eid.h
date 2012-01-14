#pragma once
#include <iostream>
using namespace std;

namespace Entity
{
template<typename tag>
class eid
{
public:
	explicit eid(const int id) : m_id(id) {}
	eid(const eid<tag>& rhs) : m_id(rhs.m_id) {}
	eid<tag>& operator=(const eid<tag>& rhs) { m_id = rhs.m_id; return *this; }
	operator int () const { return m_id; }
	bool operator==(const eid<tag>& rhs) const { return m_id == rhs.m_id; }
	bool operator<(const eid<tag>& rhs) const { return m_id < rhs.m_id; }
	
private:
	int m_id;
};

}//namespace

