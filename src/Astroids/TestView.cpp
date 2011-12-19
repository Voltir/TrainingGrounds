#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "EntitySystem.h"
#include "View.h"
using namespace std;
using namespace Entity;

struct FooComponent
{
	int foo_data;
};

class FooSystem
{
public:
	typedef FooComponent Component;
};

class BarSystem
{
public:
	typedef FooComponent Component;
};

class BazSystem
{
public:
	typedef FooComponent Component;
};

TEST(EntitySystemTest,PopulateTest)
{
	Index<FooSystem, BarSystem, BazSystem> define;
	EntitySystem es(define);
	es.create(10);
	
	es.set<BarSystem>(0,new FooComponent());

	View<_not<_has<BarSystem>>> v(&es);

	ASSERT_EQ(distance(v.begin(),v.end()),9);

	for(int eid: v)
	{
		es.set<BarSystem>(eid,new FooComponent());
	}
	
	ASSERT_EQ(distance(v.begin(),v.end()),0);

	es.create(5);
	
	int base = 10;
	for(int eid: v)
	{
		ASSERT_EQ(eid,base++);
	}
}	
