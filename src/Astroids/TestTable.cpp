#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "Table.h"
#include "Definition.h"
#include "ComponentStore.h"

//TODO Figure out how to make multiple instances of the *same* Table work nicely 
// -- need to ensure definition is the same

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

//A tag to define the testing universe
class test {};
class other {};

TEST(TableTest,ExpectedUsageTest)
{
	//Expected usage is like so...
	/////////////Definition<test,_dense<Foo>,_sparse<Bar>,_dense<Baz>> def;
	Definition<test,_dense<Foo>,_dense<Bar>,_dense<Baz>> def;
	Table<test> wat(def);
	//We would like to have 10 entities avilable to us
	wat.create(10);

	//Normally we would use a View class to access this table
	//but we can create eids (Entity ID aka primary key) directly
	eid<test> a(0);

	//And basic usage is thus
	ASSERT_FALSE(wat.has<Foo>(a));

	//while this is a compile time error
	eid<other> b(0); //note the tag parameter
	//wat.has<Foo>(b); <-- Nice.

	//And we assign elements like so
	wat.set<Foo>(a,new Foo()); //ownership is given to the table
	
	ASSERT_TRUE(wat.has<Foo>(a));

	//Other components do not exist until they are "set"
	ASSERT_FALSE(wat.has<Bar>(a));

	//We can get a previously set component like so
	Foo* a_foo = wat.get<Foo>(a);
	a_foo->i = 42;

	//With the expected behavior
	ASSERT_EQ(wat.get<Foo>(a)->i,42);
}


/**** Internal testing follows, not really for usage details ****/

TEST(TableTest,EidTest)
{

	//Strongly typed entity ids! This is "inherently good".
	//Also, allows for multiple kinds of Tables to be defined
	//given how they store things internally through some static fu
	eid<test> a(0);
	eid<test> b(1);
	eid<other> f(0);
	
	//Can still used eids in the expected way
	vector<char> v = { 'a','b','c'};
	ASSERT_EQ(v[a],'a');
	ASSERT_EQ(v[b],'b');

	ASSERT_TRUE(a == f);//I wish this was a compile time error.. its not? Why C++ gods?
}

TEST(TableTest,ComponetStoreTest)
{
	eid<test> a(0);
	ComponentStore* empty = new DenseComponentStore<test,Foo>();
	DenseComponentStore<test,Foo>* t = static_cast<DenseComponentStore<test,Foo>*>(empty);
	t->create(1); //This has to be called before we can query for a -- use views to make this easy
	ASSERT_FALSE(t->has(a));
	
	delete empty; //valgrind error free up in here
}
