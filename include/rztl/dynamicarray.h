
#pragma once

#include <vector>
#include <queue>
#include <stdexcept>
#include <memory>

namespace rztl
{



	/*
	template <typename T>
	class ContiguousStorage
	{
	private:

		class Block
		{
		public:
			Block(size_t capacity)
				: m_capacity(capacity)
			{
				m_data = new T[capacity];
				m_data = std::make_unique<T[]>(capacity);
			}

			size_t GetCapacity()
			{
				return m_capacity;
			}

		private:
			size_t m_capacity;
			T* m_data;
			Block* m_next = nullptr;
			Block* m_prev = nullptr;

		};

	public:
		// Constructor to initialize the storage with a given block capacity
		ContiguousStorage(size_t blockCapacity)
			: m_blockCapacity(blockCapacity)
		{
			AllocateNewBlock();
		}

		// Request an entity from the storage
		T* RequestEntity()
		{
			if (m_freeIndices.empty())
			{
				AllocateNewBlock();
			}

			size_t index = m_freeIndices.front();
			m_freeIndices.pop();
			return m_blocks[index / m_blockCapacity].get() + (index % m_blockCapacity);
		}

		// Release an entity back to the storage
		void ReleaseEntity(T* entity)
		{
			for (size_t i = 0; i < m_blocks.size(); ++i)
			{
				T* blockStart = m_blocks[i].get();
				T* blockEnd = blockStart + m_blockCapacity;
				if (entity >= blockStart && entity < blockEnd)
				{
					size_t index = (i * m_blockCapacity) + (entity - blockStart);
					m_freeIndices.push(index);
					return;
				}
			}
			throw std::runtime_error("Invalid entity pointer");
		}

	private:
		// Allocate a new block of storage
		void AllocateNewBlock()
		{
			m_blocks.push_back(std::make_unique<T[]>(m_blockCapacity));
			size_t blockIndex = m_blocks.size() - 1;
			for (size_t i = 0; i < m_blockCapacity; ++i)
			{
				m_freeIndices.push(blockIndex * m_blockCapacity + i);
			}
		}

		size_t m_blockCapacity;
		std::vector<Block*> m_blocks;
		std::queue<size_t> m_freeIndices;
	};
	*/








template <typename T>
class DynamicArray
{
public:
	static const size_t kDefaultInitialCapacity = 16;
	static const size_t kDefaultReallocStep = 8;

protected:
	T* m_data;
	size_t m_size = 0;
	size_t m_capacity;
	size_t m_reallocStep;

	void Internal_Realloc( size_t realloc_step )
	{
		m_capacity += realloc_step;
		void* p = realloc( m_data, m_capacity * sizeof(T) );
		if( p || !m_capacity )
		{
			m_data = ((T*)p);
		}
	}

public:

	size_t GetReallocStep()
	{
		return m_reallocStep;
	}

	DynamicArray( size_t initialCapacity = kDefaultInitialCapacity, size_t reallocStep = kDefaultReallocStep )
	{
		m_capacity = initialCapacity;
		m_reallocStep = reallocStep;
		m_size = 0;
		m_data = ((T*)malloc( initialCapacity * sizeof(T) ));
	}

	virtual ~DynamicArray( )
	{
		if( m_data )
		{
			free(m_data);
		}
	}

	void Add( T item )
	{
		if( m_size+1 > m_capacity )
		{
			Internal_Realloc(m_reallocStep);
		}

		m_data[m_size] = item;
		m_size++;
	}

	T& GetBackElement()
	{
		if( !IsEmpty() )
		{
			return m_data[m_size-1];
		}
	}

	T& operator[]( size_t index )
	{
		// no error check
		return m_data[index];
	}

	void Clear()
	{
		m_size = 0;
	}

	void RemoveBackElement()
	{
		if( !IsEmpty() ) m_size--;
	}

	bool IsEmpty()
	{
		return m_size == 0;
	}

	size_t GetSize()
	{
		return m_size;
	}

	size_t GetCapacity()
	{
		return m_capacity;
	}

	T* GetRawData()
	{
		return m_data;
	}

};

}
