#pragma once

#include <vector>
#include <unordered_map>

#include "Eid.h"

namespace Entity
{

class ComponentStore
{
public:
	virtual ~ComponentStore(){} 
	virtual void create(int amount) =0;
};

template <typename tag, typename ComponentT>
class Accessor : public ComponentStore
{
public:
	virtual ~Accessor(){}
	virtual void create(int amount) =0;
	virtual ComponentT* get(const eid<tag>& e) =0;
	virtual void set(const eid<tag>& e, ComponentT* component) =0;
	virtual bool has(const eid<tag>& e) const =0;
};

/****** Dense Definition ******/

template <typename tag, typename ComponentT> 
class DenseComponentStore 
	: public Accessor<tag,ComponentT>
{
public:
	virtual ~DenseComponentStore();
	virtual void create(int amount);
	virtual ComponentT* get(const eid<tag>& e);
	virtual void set(const eid<tag>& e, ComponentT* component);
	virtual bool has(const eid<tag>& e) const;
	std::vector<ComponentT*> m_data;
};


template <typename tag, typename ComponentT>
DenseComponentStore<tag,ComponentT>::~DenseComponentStore()
{
	for(ComponentT* comp : m_data)
	{
			delete comp;
	}
	m_data.clear();
}

template <typename tag, typename ComponentT>
void DenseComponentStore<tag,ComponentT>::create(int amount)
{
	using namespace std;
	for(int i=0; i<amount; ++i)
	{
		m_data.push_back(NULL);
	}
}

template <typename tag, typename ComponentT>
ComponentT* 
DenseComponentStore<tag,ComponentT>::get(const eid<tag>& e)
{
	assert(e < m_data.size());
	return m_data[e];
}

template <typename tag, typename ComponentT>
void DenseComponentStore<tag,ComponentT>::set(const eid<tag>& e, ComponentT* component)
{
	assert(e < m_data.size());
	m_data[e] = component;
}

template <typename tag, typename ComponentT>
bool DenseComponentStore<tag,ComponentT>::has(const eid<tag>& e) const
{
	assert(e < m_data.size());
	return m_data[e] != NULL;
}

/****** Sparse Definition ******/

template <typename tag, typename ComponentT> 
class SparseComponentStore 
	: public Accessor<tag,ComponentT>
{
public:
	virtual void create(int amount) { }
	virtual ComponentT* get(const eid<tag>& e) {return 0;}
	virtual void set(const eid<tag>& e, ComponentT* component);
	virtual bool has(const eid<tag>& e) const {
		using namespace std;
		cout << "HOLY FUCK SPARSE HAS" << endl;
		return false;
	}

//private:
//	std::unordered_map<int,ComponentT*> m_data;
};


template <typename tag, typename ComponentT>
void SparseComponentStore<tag,ComponentT>::set(const eid<tag>& e, ComponentT* component)
{
	using namespace std;
	cout << "SET SPARSE" << endl;
}

}//namespace
