#pragma once
#include <iostream>
using namespace std;
using namespace Entity;


/*
template <typename... Input> struct Index;

template <typename Head> struct Index<Head>
{
	static int index;

	template<int N>
	void __generate() { index = N; }	
};

template<typename Head>
int Index<Head>::index = -1;

template<typename Input, typename... Rest> 
struct Index<Input,Rest...>
{
	void init() { __generate<0>(); }

	template<int N>
	void __generate()
	{
		Index<Input>::index = N;
		Index<Rest...> rest;
		rest.__generate<N+1>();
	}
};

class Whatz
{
public:
	template<typename Thing>
	int foo() { return Index<Thing>::index; }
};
*/

template <typename SystemType>
struct _has
{
	static bool evaluate(const EntitySystem& es)
	{
		return es.has<SystemType>(0);
	}
};

template <typename PredicateType>
struct _not
{
	static bool evaluate(const EntitySystem& es)
	{
		return !PredicateType::evaluate(es);
	}
};

template <typename... Inputs>
struct _and
{
	static bool evaluate(const EntitySystem& es) { }
};

template <typename Head, typename... Tail>
struct _and<Head,Tail...>
{
	static bool evaluate(const EntitySystem& es)
	{
		return Head::evaluate(es) && _and<Tail...>::evaluate(es);
	}
};

template <typename Head>
struct _and<Head>
{
	static bool evaluate(const EntitySystem& es) 
	{
		return Head::evaluate(es);
	}
};

struct test
{
	template <typename Foo>
	static bool testr(const Foo& f)
	{
		return f.test();
	}
};

class Whatz
{
public:
	template <typename QueryType>
	bool query(const EntitySystem& es) 
	{
		return QueryType::evaluate(es);
	}
};






struct Foo
{
	static const char* name;
	int a;
};
const char* Foo::name = "Foo";

struct Bar
{
	static const char* name;
	double b;
};
const char* Bar::name = "Bar";

struct Baz
{
	static const char* name;
	char c;
};
const char* Baz::name = "Baz";

template<class... Input>
class Crazy
{
public:
	void func()
	{
		cout << "Never! " << endl;
	}
};

template<class Input, class... Rest> 
class Crazy<Input,Rest...>
{
public:
	void func()
	{
		cout << "Wat " << Input::name << endl;
		Crazy<Rest...> test;
		test.func();
	}
};

template<class Input>
class Crazy<Input>
{
public:
	void func()
	{
		cout << "Done " << Input::name << endl;
	}
};
