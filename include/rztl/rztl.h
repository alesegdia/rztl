#pragma once


#include "matrix2d.h"
#include "dynamicarray.h"
#include "pool.h"
#include "dynamicarray.h"
#include "unordereddynamicarray.h"



namespace rztl {
	template <typename T, size_t BufferSize>
	class RingBuffer
	{
	public:
		static constexpr size_t kBufferSize = BufferSize;

		RingBuffer(const T& defaultValue)
		{
			for(size_t i = 0; i < kBufferSize; i++)
			{
				m_data[i] = defaultValue;
			}
		}

		const T& GetElement(int elementIndex) const
		{
			assert(elementIndex >= 0 && elementIndex < kBufferSize);
			auto translatedIndex = TranslateIndex(elementIndex);
			assert(translatedIndex >= 0 && translatedIndex < kBufferSize);
			return m_data[translatedIndex];
		}

		void Push(const T& elementToAdd)
		{
			m_currentStart = (m_currentStart + 1) % kBufferSize;
			m_data[m_currentStart] = elementToAdd;
			m_currentEnd = (m_currentEnd + 1) % kBufferSize;

		}

		int TranslateIndex(int index) const
		{
			return (index + m_currentStart) % kBufferSize;
		}

		size_t GetStartIndex() const
		{
			return m_currentStart;
		}

		size_t GetEndIndex() const
		{
			return m_currentEnd;
		}

	private:
		T m_data[kBufferSize];
		size_t m_currentStart = 0;
		size_t m_currentEnd = kBufferSize - 1;

	};
}
