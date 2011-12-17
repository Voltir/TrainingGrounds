#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "Component.h"
#include "EntitySystem.h"
#include "Crazy.h"

using namespace std;
struct FooComponent : public Component
{
	int foo_data;
};

class FooSystem
{
public:
	typedef FooComponent Component;
};

TEST(EntitySystemTest,Index)
{
	Index<Foo, Bar, Baz, int, double, float> define;
	define.init();

	ASSERT_EQ(Index<float>::index,5);
	ASSERT_EQ(Index<Foo>::index,0);
	ASSERT_EQ(Index<Bar>::index,1);
	ASSERT_EQ(Index<Baz>::index,2);
	ASSERT_EQ(Index<int>::index,3);
	ASSERT_EQ(Index<string>::index,-1);
}

TEST(EntitySystemTest,BasicEntityTest)
{
	Index<FooSystem, Foo> define;
	EntitySystem es(define);

	es.add(1);

	ASSERT_FALSE(es.has<FooSystem>(0));
	
	FooComponent* fc = new FooComponent();
	fc->foo_data = 42;
	es.set<FooSystem>(0,fc);
	
	ASSERT_TRUE(es.has<FooSystem>(0));
	ASSERT_EQ(es.get<FooSystem>(0)->foo_data,42);

	FooComponent* ff;
	for(int i=0;i<20000000;++i)
	{	
		if(es.has<FooSystem>(0) && i%2==1)
			ff = es.get<FooSystem>(0);
	}
	cout << ff->foo_data << endl;
}

TEST(EntitySystemTest,EntityViewTest)
{
	Index<Baz, Bar, Foo> define;
	EntitySystem es(define);//(10);

	//EntityView v = es.view();

	/*for(int i=0; i<10;++i)
	{
		es.newEntity();
		ASSERT_TRUE(v.size() == i+1);
	}
	*/

	/*
	for(eid e: view)
	{
		cout << e << endl;
	}
	*/
	//ASSERT_TRUE(v.modified());
}
