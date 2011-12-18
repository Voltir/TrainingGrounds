
#pragma once

namespace Entity
{

class ComponentSubscriber
{
public:
	virtual void publish()=0;
	//virtual void publishComponentAdded(EntitySystem* es)=1;
	//virtual void publishComponentRemoved()=0;
};

}//namespace Entity
