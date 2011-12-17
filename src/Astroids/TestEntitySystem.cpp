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

TEST(EntitySystemTest,CrazyQueryTest)
{
	_and<Foo,Bar,Baz> and_query;
	_or<Foo,Bar,Baz> or_query;
	_not<Foo> not_query;

	CrazyQuery c;

	c.what<_not<Foo>>();
	c.what<Foo>();
}
/*
TEST(EntitySystemTest,EntityViewTest)
{
	Index<FooSystem, Foo> define;
	EntitySystem es(define);
	
	es.add(5); //want to call it create

	//Views are intended to be long lived objects that track the 
	//underlying entity system

	View all_entities = es.view();

	for(int eid : all_entities)
	{
		es.set<FooSystem>(eid,new FooComponent());
	}

	View missing_foo = es.view<_not<FooSystem>>();

	es.add(10); //want to call it create

	for(int eid : missing_foo)
	{
		es.set<FooSystem>(eid,new FooComponent());
	}
}*/
