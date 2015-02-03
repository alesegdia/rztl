#pragma once

#include "./dynamicarray.h"

template <typename T>
class UnorderedDynamicArray : public DynamicArray<T>
{
public:
	UnorderedDynamicArray( size_t initial_size = DynamicArray<T>::INITIAL_SIZE )
		: DynamicArray<T>(initial_size) {}
	virtual ~UnorderedDynamicArray() {}

	void Remove( int index )
	{
		T* data = DynamicArray<T>::data;
		size_t size = DynamicArray<T>::size;
		data[index] = data[size-1];
		this->size--;
	}

private:
};

