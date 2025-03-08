#include <gtest/gtest.h>
#include "rztl/rztl.h"

namespace rztl {

template<typename T, size_t BufferSize>
struct TypeAndSize
{
	using Type = T;
	static constexpr size_t Size = BufferSize;
};

template<typename T>
class RingBufferTest : public ::testing::Test
{
protected:
	rztl::RingBuffer<typename T::Type, T::Size> buffer;

	RingBufferTest() : buffer(typename T::Type()) {}
};

using MyTypes = ::testing::Types<
	TypeAndSize<int, 10>,
	TypeAndSize<float, 20>,
	TypeAndSize<double, 30>
>;
TYPED_TEST_SUITE(RingBufferTest, MyTypes);

TYPED_TEST(RingBufferTest, InitializationTest)
{
	for(size_t i = 0; i < this->buffer.kBufferSize; ++i)
	{
		EXPECT_EQ(this->buffer.GetElement(i), typename TypeParam::Type());
	}
}

TYPED_TEST(RingBufferTest, PushTest)
{
	typename TypeParam::Type value = static_cast<typename TypeParam::Type>(42);
	this->buffer.Push(value);
	EXPECT_EQ(this->buffer.GetElement(0), 42);
}

TYPED_TEST(RingBufferTest, TranslateIndexTest)
{
	EXPECT_EQ(this->buffer.TranslateIndex(0), 0);
	EXPECT_EQ(this->buffer.TranslateIndex(1), 1);
}

TYPED_TEST(RingBufferTest, GetStartIndexTest)
{
	EXPECT_EQ(this->buffer.GetStartIndex(), 0);
}

TYPED_TEST(RingBufferTest, GetEndIndexTest)
{
	EXPECT_EQ(this->buffer.GetEndIndex(), this->buffer.kBufferSize - 1);
}

TYPED_TEST(RingBufferTest, CircularBufferTest)
{
	for(size_t i = 0; i < this->buffer.kBufferSize; ++i)
	{
		this->buffer.Push(static_cast<typename TypeParam::Type>(i));
	}
	for(size_t i = 0; i < this->buffer.kBufferSize; ++i)
	{
		EXPECT_EQ(this->buffer.GetElement(i), static_cast<typename TypeParam::Type>(i));
	}
	this->buffer.Push(static_cast<typename TypeParam::Type>(this->buffer.kBufferSize));
	EXPECT_EQ(this->buffer.GetElement(0), static_cast<typename TypeParam::Type>(1));
	EXPECT_EQ(this->buffer.GetElement(this->buffer.kBufferSize - 1), static_cast<typename TypeParam::Type>(this->buffer.kBufferSize));
}

}