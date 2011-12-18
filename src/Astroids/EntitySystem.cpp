#include "EntitySystem.h"
namespace Entity
{

void
EntitySystem::add(int amount)
{
	m_count += amount;
	for(int i=0; i<m_num_systems; ++i)
	{
		for(int j=0; j<amount; ++j)
		{
			m_component_data[i].push_back(nullptr);
		}
	}

	//TODO for each...
	for(int i=0; i<m_subscribers.size(); ++i)
	{
		m_subscribers[i]->publish();
	}
}

}//namespace Entity
