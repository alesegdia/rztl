
#pragma once

#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <cmath>

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

	struct Block {
		Block* next;
		typedef union Item {
		Placeholder<T> obj_data;
			Item* next;
		} Item;
		Item item[1];
	};


	Block* block_llist;
	typedef typename Pool<T>::Block::Item ItemType;
	ItemType *free_first, *free_last;
	size_t bytes_per_block, num_items;

	/*
	 * Reserva memoria para un bloque entero incluida la cabecera.
	 * Establece los enlaces de cada item al siguiente.
	 * Actualiza free_first y free_last con el primero y último Item del bloque respectivamente
	 */
	Block* AllocBlock()
	{
		Block *p;
		ItemType *item;
		p = ((Block*)malloc(bytes_per_block));
		// printf("Alloc'ing %d\n", p);
		free_first = p->item;
		item = ((ItemType*)((void*)p->item));
		for( int i = 0; i < num_items; i++ )
		{
			//printf("%d, ", i);
			fflush(0);
			item[i].next = item+i+1;
		}
		free_last = (item+num_items-1);
		item[num_items-1].next = NULL;
		return p;
	}

public:

	static constexpr uint16_t PAGE_SIZE = 4096;
	static constexpr uint16_t MIN_ITEMS = 32;
	static constexpr uint16_t MIN_NUM_PAGES = 2;

	/*
	 * Crea la pool calculando el tamaño de bloque para que tenga como
	 * mínimo, count_items_per_block, alojando en número de páginas
	 * para favorecer el acierto a accesos de memoria
	 */
	Pool( uint32_t count_items_per_block = MIN_ITEMS )
	{
		// numero de paginas por bloque
		size_t num_pages = ceil(float(count_items_per_block * sizeof(T)) / float(PAGE_SIZE));
		if( num_pages < MIN_NUM_PAGES ) num_pages = MIN_NUM_PAGES;

		// numero de items por bloque
		size_t sizeofitem = sizeof(ItemType);
		num_items = floor(( float(num_pages * 4096) ) / float(sizeofitem));

		// numero de bytes por bloque
		// cabecera (incluye un item)     + numero restante de items
		bytes_per_block = sizeof( Block ) + sizeofitem * ( num_items - 1 );

		printf("num_pages = %lu\n", num_pages);
		printf("num_items = %lu\n", num_items);
		printf("sizeof(Block) = %lu\n", sizeof(Block));
		printf("sizeof(T) = %lu\n", sizeof(T));
		printf("sizeofitem = %lu\n", sizeofitem);
		printf("sizeof(decltype...) = %lu\n", sizeof(decltype(block_llist->item[0])));
		printf("bytesperblock: %lu\n", bytes_per_block);
		printf("itemsperblock: %f\n", floor(((float)bytes_per_block)/((float)num_items)));

		// pedir primer bloque y establecer enlace
		block_llist = AllocBlock();
		block_llist->next = NULL;
	}

	~Pool(){
		// borramos todos los bloques
		Block *current, *next;
		current = block_llist;
		while( ((void*)current) != NULL )
		{
			printf("Trying to free %d\n", current);
			next = current->next;
			free(current);
			current = next;
		}
	}

	/*
	 * Se construye despues de avanzar el free_first para no sobreescribir el next
	 * del free_first y poderlo avanzar.
	 */
	template <typename...ARGS>
	T* Create(ARGS&&...args)
	{
		// si esta lleno, reservamos bloque nuevo al final
		if( (void*) free_first == NULL )
		{
			Block* new_block, *current_block, *prev_block;

			// creamos el bloque nuevo
			new_block = AllocBlock();

			// nos vamos al último
			current_block = block_llist;
			while( ((void*)current_block) != NULL )
			{
				prev_block = current_block;
				current_block = current_block->next;
			}

			// colocamos el nuevo en el último
			prev_block->next = ((Block*)new_block);
			new_block->next = NULL;

			// actualizamos el free_first y free_last
			free_first = new_block->item;
			free_last = new_block->item+num_items-1;
		}

		T* obj = (T*)&(free_first->obj_data);
		free_first=free_first->next;

		new (obj) T(args...);
		return obj;
	}

	/*
	 * Llama al destructor del objeto y asigna el free_first
	 */
	void Destroy( T* e )
	{
		e->~T();
		free_last = (ItemType*)e;
	}


};

}
