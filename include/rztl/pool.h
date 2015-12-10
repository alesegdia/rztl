
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
		Item() : state{} {}
		~Item() {}
		T obj_data;
		struct {
			Item* next;
			bool in_use = false;
		} state;
	};


	Item *free_first, *free_last;
	size_t bytes_per_block, num_items;
	std::vector<Item*> block_list;

	// ugly fix!
	std::vector<T*> items_in_use;

	void AllocBlock()
	{
		// allocate items
		Item* new_block = new Item[100];

		// build linked list of free elements
		for( int i = 0; i < 100; i++ )
		{
			new_block[i].state.next = new_block+i+1;
		}

		// mark last pool element
		new_block[99].state.next = NULL;

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
		for( auto it : items_in_use )
		{
			it->~T();
		}
		for( auto it : block_list )
		{
			i++;
			delete [] it;
		}
	}

	template <typename...ARGS>
	T* Create(ARGS&&...args)
	{
		if( free_first->state.next == NULL )
		{
			AllocBlock();
		}

		Item* item = free_first;
		free_first = free_first->state.next;

		T* obj = new(&item->obj_data) T(args...);
		items_in_use.push_back(obj);

		return obj;
	}

	/*
	 * Llama al destructor del objeto y asigna el free_first
	 */
	void Destroy( T* e )
	{
		items_in_use.erase( std::find( items_in_use.begin(), items_in_use.end(), e ) );
		e->~T();
		free_last->state.next = (Item*)e;
		free_last = (Item*)e;
		free_last->state.next = NULL;
	}


};

}
