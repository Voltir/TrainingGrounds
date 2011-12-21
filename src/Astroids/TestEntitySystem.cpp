#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "Component.h"
#include "EntitySystem.h"
//#include "Crazy.h"
#include "View.h"
//TODO: Define a constrctor for Index with a single systme...

using namespace std;
using namespace Entity;

struct Foo
{
	int i;
};

struct Bar
{
	double d;
};

struct Baz
{
	string s;
};

TEST(EntitySystemTest,Index)
{
/*
	Index<Foo, Bar, Baz, int, double, float> define;
	define.init();

	ASSERT_EQ(Index<float>::index,5);
	ASSERT_EQ(Index<Foo>::index,0);
	ASSERT_EQ(Index<Bar>::index,1);
	ASSERT_EQ(Index<Baz>::index,2);
	ASSERT_EQ(Index<int>::index,3);
	ASSERT_EQ(Index<string>::index,-1);
*/
}

TEST(EntitySystemTest,DefinitionTest)
{
	Definition<_dense<Foo>,_sparse<Bar>,_dense<Baz>> def;
	def.__generate();

	Definition<Foo>::set(0,new Foo);
	Definition<Bar>::set(0,new Bar);
	Definition<Baz>::set(0,new Baz);
	//Definition<Bar>::set();
	//Definition<Baz>::set();
}

TEST(EntitySystemTest,BasicEntityTest)
{
	Index<Foo, Bar> define;
	EntitySystem es(define);

	es.create(1);

	ASSERT_FALSE(es.has<Foo>(0));
	
	Foo* fc = new Foo();
	fc->i = 42;
	es.set<Foo>(0,fc);
	
	ASSERT_TRUE(es.has<Foo>(0));
	ASSERT_EQ(es.get<Foo>(0)->i,42);

	Foo* ff;
	for(int i=0;i<20000000;++i)
	{	
		if(es.has<Foo>(0) && i%2==1)
			ff = es.get<Foo>(0);
	}
	cout << ff->i << endl;
}
