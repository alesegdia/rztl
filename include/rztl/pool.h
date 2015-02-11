
#pragma once

#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <vector>

namespace rztl
{

template <typename T>
class Placeholder
{
private:
	uint8_t bytes[sizeof(T)];
public:
	operator T& () { return (T*)bytes; }
	operator const T& () const { return (T*)bytes; }
};

template <typename T>
class Pool
{

private:

	union Item {
		Item() : next{} {}
		~Item() {}
		T obj_data;
		Item* next;
	};


	Item *free_first, *free_last;
	size_t bytes_per_block, num_items;
	std::vector<Item*> block_list;

	void AllocBlock()
	{
		// allocate items
		Item* new_block = new Item[100];

		// build linked list of free elements
		for( int i = 0; i < 100; i++ )
		{
			new_block[i].next = &(new_block[i+1]);
		}

		// mark last pool element
		new_block[99].next = NULL;

		// assign first available item
		free_first = new_block;

		free_last = &new_block[99];

		// push block to block_list
		block_list.push_back(new_block);
	}

public:

	static constexpr uint16_t PAGE_SIZE = 4096;
	static constexpr uint16_t MIN_ITEMS = 32;
	static constexpr uint16_t MIN_NUM_PAGES = 2;

	Pool( uint32_t count_items_per_block = MIN_ITEMS )
	{
		AllocBlock();
	}

	~Pool(){
		int i = 0;
		for( auto it : block_list )
		{
			i++;
			Item* iter = it;
			while(iter)
			{
				iter->~Item();
				iter = iter->next;
			}
			delete [] it;
		}
		printf("eliminados %d elementos.\n", i);
	}

	template <typename...ARGS>
	T* Create(ARGS&&...args)
	{
		if( free_first->next == NULL )
		{
			AllocBlock();
		}

		Item* item = free_first;
		free_first = free_first->next;

		T* obj = new(&item->obj_data) T();

		return obj;
	}

	/*
	 * Llama al destructor del objeto y asigna el free_first
	 */
	void Destroy( T* e )
	{
		e->~T();
		free_last->next = (Item*)e;
		free_last = (Item*)e;
		free_last->next = NULL;
	}


};

}
