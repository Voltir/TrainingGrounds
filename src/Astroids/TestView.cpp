#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "EntitySystem.h"
#include "View.h"
#include "QueryPredicates.h"
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

class vtest {} ;

TEST(ViewTest,PopulateTest)
{
	Definition<vtest,_dense<Foo>,_dense<Bar>,_dense<Baz>> def;
	Table<vtest> table(def);
	table.create(10);

	eid<vtest> a(0);
	table.set<Bar>(a,new Bar());

	View<vtest,_not<_has<Bar>>> v(&table);
	
	int count = 9;
	
	ASSERT_EQ(distance(v.begin(),v.end()),count--);
	
	for(eid<vtest> e: v)
	{
		table.set<Bar>(e,new Bar());
		ASSERT_EQ(distance(v.begin(),v.end()),count--);
	}
	
	ASSERT_EQ(distance(v.begin(),v.end()),0);

	table.create(5);
	
	int base = 10;
	for(eid<vtest> e: v)
	{
		ASSERT_EQ(e,base++);
	}
}	
