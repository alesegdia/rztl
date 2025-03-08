#pragma once


#include "matrix2d.h"
#include "dynamicarray.h"
#include "pool.h"
#include "dynamicarray.h"
#include "unordereddynamicarray.h"



namespace rztl {
	template <typename T, size_t BufferSize>
	class SnapshotBuffer
	{
	public:
		static constexpr size_t kBufferSize = BufferSize;

		SnapshotBuffer(const T& defaultValue)
		{
			m_data = new T[capacity];
			m_currentTop = 0;
			for(size_t i = 0; i < kBufferSize; i++)
			{
				m_data[i] = defaultValue;
			}
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
			m_currentTop = (m_currentTop + 1) % m_capacity;

			m_data[m_capacity] = elementToAdd;
			m_currentBottom = (m_currentBottom + 1) % m_capacity;

		}

	private:
		int TranslateIndex(int index)
		{
			return index + m_currentTop % kBufferSize;
		}

		size_t GetTopIndex()
		{
			return m_currentTop;
		}

		size_t GetBottomIndex()
		{
			return m_currentBottom;
		}

		T* m_data;
		size_t m_capacity;
		size_t m_currentTop;
		size_t m_currentBottom;

	};
}
