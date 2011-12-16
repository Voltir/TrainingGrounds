#pragma once
#include <iostream>
using namespace std;

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
