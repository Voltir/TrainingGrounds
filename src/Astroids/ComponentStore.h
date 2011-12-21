#pragma once

#include <vector>
#include <unordered_map>

//ComponentStore will hold the actual component data
template <typename ComponentT>
class ComponentStore
{
public:
	virtual ComponentT* get(int e)=0;
	virtual void set(int e, ComponentT* component)=0;
	virtual bool has(int e)=0;
};

template <typename ComponentT> 
class DenseComponentStore : public ComponentStore<ComponentT>
{
public:
	virtual ComponentT* get(int e){ return 0;}
	virtual void set(int e, ComponentT* component);
	virtual bool has(int e){ return false;}

private:
	std::vector<ComponentT*> m_data;
};

template <typename ComponentT> 
class SparseComponentStore : public ComponentStore<ComponentT>
{
public:
	virtual ComponentT* get(int e) {return 0;}
	virtual void set(int e, ComponentT* component);
	virtual bool has(int e) {return false;}

private:
	std::unordered_map<int,ComponentT*> m_data;
};

//Dense Definition
template <typename ComponentT>
void DenseComponentStore<ComponentT>::set(int e, ComponentT* component)
{
	using namespace std;
	cout << "SET DENSE" << endl;
}

//Sparse Definition
template <typename ComponentT>
void SparseComponentStore<ComponentT>::set(int e, ComponentT* component)
{
	using namespace std;
	cout << "SET SPARSE" << endl;
}
