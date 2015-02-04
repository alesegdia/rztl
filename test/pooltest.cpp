
#include <cstdio>
#include "pool.h"
#include <vector>

struct Foo {
	int bar[20];
	Foo(int a){}
	~Foo(){}
};

int main( int argc, char** argv )
{
	Pool<Foo> pool(32);
	std::vector<Foo*> vec;

	for( int i = 0; i < 1600; i++ )
	{
		printf("%d, ", i);
		vec.push_back(pool.Create(3));
	}

	return 0;
}
