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
	cout << Index<float>::index << endl;
	cout << Index<Foo>::index << endl;
	cout << Index<Bar>::index << endl;
	cout << Index<Baz>::index << endl;
	cout << Index<int>::index << endl;
	cout << Index<double>::index << endl;
	cout << Index<string>::index << endl;
}

TEST(EntitySystemTest,What)
{
	Index<Baz, Bar, Foo> define;
	define.init();
	Whatz what;

	cout << what.foo<Foo>() << endl;
	cout << what.foo<Bar>() << endl;
	cout << what.foo<Baz>() << endl;
}
TEST(EntitySystemTest,Crazy)
{
	Crazy<Foo,Bar,Baz, Foo, Foo , Foo> c;
	c.func();
}

TEST(EntitySystemTest,EntityAddTest)
{
	Index<FooSystem, Foo> define;
	EntitySystem es(define);

	es.newEntity();
	es.newEntity();
	es.newEntity();

	FooComponent* f = es.get<FooSystem>(0);
	cout << "A Wat " << f << endl;

	FooComponent* fc = new FooComponent();
	fc->foo_data = 42;
	es.set<FooSystem>(0,fc);

	for(int i=0;i<20000000;++i)
	{	
		if(es.has<FooSystem>(0))
			FooComponent* ff = es.get<FooSystem>(0);
		//Component* ff = es.fast<FooSystem>(0);
	}
	FooComponent* ff = es.get<FooSystem>(0);
	cout << "B Wat " << ff->foo_data << endl;
	cout << es.has<FooSystem>(0) << " " << es.has<FooSystem>(1) << endl;

	vector<int> test;
	test.push_back(42);	
	for(int i=0;i<20000000;++i)
	{
		int a = test[0];	
	}
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
