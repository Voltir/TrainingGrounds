#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "EntitySystem.h"
#include "View.h"
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

TEST(ViewTest,PopulateTest)
{
	Index<Foo, Bar, Baz> define;
	EntitySystem es(define);
	es.create(10);
	
	es.set<Bar>(0,new Bar());

	View<_not<_has<Bar>>> v(&es);

	int count = 9;

	ASSERT_EQ(distance(v.begin(),v.end()),count--);

	for(int eid: v)
	{
		es.set<Bar>(eid,new Bar());
		ASSERT_EQ(distance(v.begin(),v.end()),count--);
	}
	
	ASSERT_EQ(distance(v.begin(),v.end()),0);

	es.create(5);
	
	int base = 10;
	for(int eid: v)
	{
		ASSERT_EQ(eid,base++);
	}
}	
