#pragma once


#include "matrix2d.h"
#include "dynamicarray.h"
#include "pool.h"
#include "dynamicarray.h"
#include "unordereddynamicarray.h"



namespace rztl {
	template <typename T>
	class SnapshotBuffer
	{
	public:
		SnapshotBuffer(size_t capacity)
			: m_capacity(capacity)
		{
			m_data = new T[capacity];
			m_currentTop = 0;
		}

		~SnapshotBuffer()
		{
			delete[] m_data;
		}

		T& GetElement(int elementIndex)
		{
			assert(elementIndex >= 0 && elementIndex < m_capacity);
			auto translatedIndex = TranslateIndex(elementIndex);
			assert(translatedIndex >= 0 && translatedIndex < m_capacity);
			return m_data[translatedIndex];
		}

		size_t GetCapacity() const
		{
			return m_capacity;
		}

		void Push(const T& elementToAdd)
		{
			m_data[m_capacity] = elementToAdd;
			m_capacity++;
			m_currentTop = (m_currentTop + 1) % m_capacity;
		}

	private:
		int TranslateIndex(int index)
		{
			return index + m_currentTop % m_capacity;
		}

		T* m_data;
		size_t m_capacity;
		size_t m_currentTop;

	};
}
