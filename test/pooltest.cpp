
#include <cstdio>
#include "../include/pool.h"
#include <vector>

struct Foo {
	int bar[20];
	Foo(int a){}
	~Foo(){}
};

int main( int argc, char** argv )
{
	rztl::Pool<Foo> pool(32);
	std::vector<Foo*> vec[2];

	for( int i = 0; i < 3000; i++ )
	{
		vec[0].push_back(pool.Create(3));
	}

	for( int i = 0; i < 1500; i++ )
	{
		pool.Destroy( vec[0].back() );
		vec[0].pop_back();
	}

	for( int i = 0; i < 6000; i++ )
	{
		vec[1].push_back(pool.Create(3));
	}

	for( int i = 0; i < 1000; i++ )
	{
		pool.Destroy( vec[0].back() );
		vec[0].pop_back();
	}

	for( int i = 0; i < 3000; i++ )
	{
		pool.Destroy( vec[1].back() );
		vec[1].pop_back();
	}

	for( int i = 0; i < 10000; i++ )
	{
		pool.Create(3);
	}

	return 0;
}
