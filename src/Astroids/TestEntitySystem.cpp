#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "EntitySystem.h"
#include "Crazy.h"

using namespace std;

TEST(EntitySystemTest,Crazy)
{
	Crazy<Foo,Bar,Baz> c;
	c.func();
}

TEST(EntitySystemTest,EntityViewTest)
{
	EntitySystem es;//(10);
	EntityView v = es.view();

	for(int i=0; i<10;++i)
	{
		es.newEntity();
		ASSERT_TRUE(v.size() == i+1);
	}

	for(eid e: view)
	{
		cout << e << endl;
	}
	//ASSERT_TRUE(v.modified());
}

/*
TEST(EntitySystemTest,Foo)
{
	EntitySystem es(10);

	for(int i=0; i<10;++i)
	{
		eid e = es.newEntity();
		es.bind<SystemA::component>(e,comp);
	}

	EntityViewFilter evf((SystemA||SystemB)&&SystemC);
	EntityView v = es.view(evf);
	for(eid e : view)
	{
		if(es.has<SystemA>(e))
		{
			SystemA::component& foo = es.get<SystemA>(e);
		}
		SystemC::component& bar = es.get<SystemC>(e);
	}
}
*/
