
#include <chrono>
#include <iostream>
#include <new>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <tuple>
#include <vector>

template <typename Class, typename T>
struct Offset {
	static size_t offset;
};

template <typename Class, typename T>
size_t Offset<Class, T>::offset = 0;

template <typename Class, typename... Rest>
struct ComputeOffset;

template <typename Class, typename First, typename... Rest>
struct ComputeOffset<Class, First, Rest...>
{
	static size_t computeOffset() {
		size_t restsize = ComputeOffset<Class, Rest...>::computeOffset();
		Offset<Class, First>::offset = restsize;
		return sizeof(First) + restsize;
	}
};

template <typename Class>
struct ComputeOffset<Class> {
	static size_t computeOffset() {
		return 0;
	}
};

template <typename Class, typename... Rest>
struct ComputeSize;

template <typename Class, typename First, typename... Rest>
struct ComputeSize<Class, First, Rest...>
{
	static constexpr size_t getSize() {
		return sizeof(First) + ComputeSize<Class, Rest...>::getSize();
	}
};

template <typename Class>
struct ComputeSize<Class> {
	static constexpr size_t getSize() {
		return 0;
	}
};


template <typename Class, typename... Rest>
struct ChunkAllocator;

template <typename Class, typename First, typename... Rest>
struct ChunkAllocator<Class, First, Rest...>
{
	static void alloc(char* base_ptr) {
		void* place = base_ptr + Offset<Class, First>::offset;
		First* obj = new (place) First();
		ChunkAllocator<Class, Rest...>::alloc(base_ptr);
	}
};

template <typename Class>
struct ChunkAllocator<Class>
{
	static void alloc(char* base_ptr) {

	}
};


template <typename SubClass, int NUM_ELEMENTS, typename... Types>
class MultiPoolFactory
{
private:
	typedef struct ItemType  { char m_bytes[ComputeSize<SubClass, Types...>::getSize()]; } ItemType;
	const size_t m_chunkSize = ComputeSize<SubClass, Types...>::getSize();
	size_t m_lastAlloc = 0;

public:

	char *m_bytes;
	MultiPoolFactory() {
		ComputeOffset<SubClass, Types...>::computeOffset();
		m_bytes = new char[m_chunkSize * NUM_ELEMENTS];
		for( int i = 0; i < NUM_ELEMENTS; i++ ) {
		}
	}

	~MultiPoolFactory() {
		delete [] m_bytes;
	}

	void allocChunk() {
		ChunkAllocator<SubClass, Types...>::alloc(m_bytes + m_lastAlloc * m_chunkSize);
		m_lastAlloc++;
	}

	size_t getChunkSize() {
		return m_chunkSize;
	}

	template <typename T>
	T* getItemForIndex( size_t index ) {
		char* location = m_bytes + index * m_chunkSize + Offset<SubClass, T>::offset;
		return ((T*)(location));
	}

	template <typename T>
	size_t getOffsetForType() {
		return Offset<SubClass, T>::offset;
	}

	template <typename T>
	size_t getSizeFor() {
		return sizeof(T);
	}
};


struct A {
	std::uint8_t a = 0;
	std::uint16_t b = 0;
	std::uint16_t c = 0;
	std::uint16_t d = 0;
	std::uint16_t e = 0;
};

struct B {
	std::uint16_t a = 0;
	std::uint32_t b = 0;
	std::uint32_t c = 0;
	std::uint32_t d = 0;
	std::uint32_t e = 0;
};

struct C {
	std::uint16_t a;
	std::uint32_t b;
};

template <typename... Types>
using multipool_t = std::vector<std::tuple<Types...>> ;

class TestPool1 : public MultiPoolFactory<TestPool1, 10, A, B, C> {};
class TestPool2 : public MultiPoolFactory<TestPool2, 10, C, A, B> {};

int main( int argc, char** argv )
{

	TestPool1 tp1;
	TestPool2 tp2;

	tp1.allocChunk();
	tp1.allocChunk();
	tp1.allocChunk();
	tp1.allocChunk();

	A* a0 = tp1.getItemForIndex<A>(0);
	A* a1 = tp1.getItemForIndex<A>(1);
	A* a2 = tp1.getItemForIndex<A>(2);
	A* a3 = tp1.getItemForIndex<A>(3);

	B* b0 = tp1.getItemForIndex<B>(0);
	B* b1 = tp1.getItemForIndex<B>(1);
	B* b2 = tp1.getItemForIndex<B>(2);
	B* b3 = tp1.getItemForIndex<B>(3);

	C* c0 = tp1.getItemForIndex<C>(0);
	C* c1 = tp1.getItemForIndex<C>(1);
	C* c2 = tp1.getItemForIndex<C>(2);
	C* c3 = tp1.getItemForIndex<C>(3);

	multipool_t<A,B,C> mp1;
	multipool_t<C,A,B> mp2;

	return 0;
}
