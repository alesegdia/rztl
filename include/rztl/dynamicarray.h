
#pragma once

#include <cstdint>
#include <cstdlib>

namespace rztl
{

template <typename T>
class DynamicArray
{

protected:

	static const size_t INITIAL_SIZE = 128;
	static const size_t REALLOC_STEP = 16;

	T* m_data;
	size_t m_size = 0;
	size_t m_capacity;

	void realloc( size_t realloc_step = REALLOC_STEP )
	{
		m_capacity += realloc_step;
		void* p = realloc( m_data, m_capacity * sizeof(T) );
		if( p || !m_capacity )
		{
			m_data = ((T*)p);
		}
	}

public:

	DynamicArray( size_t initial_size = INITIAL_SIZE )
	{
		m_capacity = initial_size;
		m_size = 0;
		m_data = ((T*)malloc( initial_size * sizeof(T) ));
	}

	virtual ~DynamicArray( )
	{
		if( m_data )
		{
			free(m_data);
		}
	}

	void add( T item )
	{
		if( m_size+1 > m_capacity )
		{
			realloc();
		}

		m_data[m_size] = item;
		m_size++;
	}

	T& back()
	{
		if( !isEmpty() )
		{
			return m_data[m_size-1];
		}
	}

	T& operator[]( size_t index )
	{
		// no error check
		return m_data[index];
	}

	void clear()
	{
		m_size = 0;
	}

	void removeLast()
	{
		if( !isEmpty() ) m_size--;
	}

	bool isEmpty()
	{
		return m_size == 0;
	}

	size_t size()
	{
		return m_size;
	}

	T* getRawData()
	{
		return m_data;
	}

};

}
