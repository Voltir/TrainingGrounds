
#pragma once

namespace Entity
{

class ComponentSubscriber
{
public:
	virtual void publishAfterCreate(int eid)=0;
	virtual void publishAfterAdd(int eid)=0;
	//virtual void publishBeforeRemove(int eid)=0;
};

}//namespace Entity
