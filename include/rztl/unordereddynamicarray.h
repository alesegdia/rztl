#pragma once

#include "./dynamicarray.h"

namespace rztl
{

template <typename T>
class UnorderedDynamicArray : public DynamicArray<T>
{
public:
	UnorderedDynamicArray( size_t initial_size = DynamicArray<T>::INITIAL_SIZE )
		: DynamicArray<T>(initial_size) {}
	virtual ~UnorderedDynamicArray() {}

	void removeIndex( int index )
	{
		this->m_data[index] = this->m_data[this->m_size-1];
		this->m_size--;
	}

	void remove( T object )
	{
		size_t i = 0;
		while( i < this->m_size )
		{
			if( object == this->m_data[i] ) break;
			i++;
		}
		removeIndex(i);
	}

private:
};

}
