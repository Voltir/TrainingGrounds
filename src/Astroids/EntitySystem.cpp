#include "EntitySystem.h"
#include <iostream>

using namespace std;

namespace Entity
{

void
EntitySystem::create(int amount)
{
	m_size += amount;

	for(int i=0; i<m_num_systems; ++i)
		for(int j=0; j<amount; ++j)
			m_component_data[i].push_back(nullptr);
	
	for(int i=amount; 0 < i; --i)
		for(auto s: m_subscribers)
			s->publishAfterCreate(m_size - i);
}

}//namespace Entity
