#pragma once
#include <iostream>
using namespace std;

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
