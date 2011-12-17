#pragma once

template <typename... List> struct Index;

template <typename Head> struct Index<Head>
{
	static int index;
	template<int N>
	void __generate() { index = N; }	
};

template<typename Head>
int Index<Head>::index = -1;

template<typename Head, typename... Tail> 
struct Index<Head,Tail...>
{
	void init() { __generate<0>(); }
	
	template<int N>
	void __generate()
	{
		Index<Head>::index = N;
		Index<Tail...> rest;
		rest.__generate<N+1>();
	}
};
