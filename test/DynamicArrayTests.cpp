#include <gtest/gtest.h>
#include "rztl/dynamicarray.h"

namespace rztl {

TEST(DynamicArrayTest, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.GetSize(), 0);
    EXPECT_EQ(arr.GetCapacity(), DynamicArray<int>::kDefaultInitialCapacity);
}

TEST(DynamicArrayTest, ParameterizedConstructor) {
    DynamicArray<int> arr(10, 5);
    EXPECT_EQ(arr.GetSize(), 0);
    EXPECT_EQ(arr.GetCapacity(), 10);
}

TEST(DynamicArrayTest, AddElement) {
    DynamicArray<int> arr;
    arr.Add(5);
    EXPECT_EQ(arr.GetSize(), 1);
    EXPECT_EQ(arr[0], 5);
}

TEST(DynamicArrayTest, AddMultipleElements) {
    const int initialCapacity = 10;
    const int reallocStep = 7;
    DynamicArray<int> arr(initialCapacity, reallocStep);
    for (int i = 0; i < 100; ++i) {
        arr.Add(i);
    }
    EXPECT_EQ(arr.GetSize(), 100);
    int expectedCapacity = initialCapacity + ((100 - initialCapacity + reallocStep - 1) / reallocStep) * reallocStep;
    EXPECT_EQ(arr.GetCapacity(), expectedCapacity);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(DynamicArrayTest, AddElementWithRealloc) {
    DynamicArray<int> arr(2, 2); // Initial capacity 2, realloc step 2
    arr.Add(1);
    arr.Add(2);
    arr.Add(3);
    EXPECT_EQ(arr.GetSize(), 3);
    EXPECT_EQ(arr.GetCapacity(), 4); // 2 initial + 1 realloc step of 2
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArrayTest, GetBackElement) {
    DynamicArray<int> arr;
    arr.Add(5);
    arr.Add(10);
    EXPECT_EQ(arr.GetBackElement(), 10);
}

TEST(DynamicArrayTest, Clear) {
    DynamicArray<int> arr;
    arr.Add(5);
    arr.Add(10);
    arr.Clear();
    EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, RemoveBackElement) {
    DynamicArray<int> arr;
    arr.Add(5);
    arr.Add(10);
    arr.RemoveBackElement();
    EXPECT_EQ(arr.GetSize(), 1);
    EXPECT_EQ(arr.GetBackElement(), 5);
}

TEST(DynamicArrayTest, RemoveMultipleBackElements) {
    const int initialCapacity = 10;
    const int reallocStep = 7;
    DynamicArray<int> arr(initialCapacity, reallocStep);
    for (int i = 0; i < 100; ++i) {
        arr.Add(i);
    }
    for (int i = 0; i < 50; ++i) {
        arr.RemoveBackElement();
    }
    EXPECT_EQ(arr.GetSize(), 50);
    int expectedCapacity = initialCapacity + ((100 - initialCapacity + reallocStep - 1) / reallocStep) * reallocStep;
    EXPECT_EQ(arr.GetCapacity(), expectedCapacity);
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(DynamicArrayTest, IsEmpty) {
    DynamicArray<int> arr;
    EXPECT_TRUE(arr.IsEmpty());
    arr.Add(5);
    EXPECT_FALSE(arr.IsEmpty());
}

TEST(DynamicArrayTest, GetRawData) {
    DynamicArray<int> arr;
    arr.Add(5);
    arr.Add(10);
    int* rawData = arr.GetRawData();
    EXPECT_EQ(rawData[0], 5);
    EXPECT_EQ(rawData[1], 10);
}

TEST(DynamicArrayTest, AddAndRemoveMultipleElements) {
    const int initialCapacity = 10;
    const int reallocStep = 7;
    DynamicArray<int> arr(initialCapacity, reallocStep);
    for (int i = 0; i < 100; ++i) {
        arr.Add(i);
    }
    for (int i = 0; i < 50; ++i) {
        arr.RemoveBackElement();
    }
    for (int i = 0; i < 50; ++i) {
        arr.Add(i + 100);
    }
    EXPECT_EQ(arr.GetSize(), 100);
    int expectedCapacity = initialCapacity + ((100 - initialCapacity + reallocStep - 1) / reallocStep) * reallocStep;
    EXPECT_EQ(arr.GetCapacity(), expectedCapacity);
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(arr[i], i);
    }
    for (int i = 50; i < 100; ++i) {
        EXPECT_EQ(arr[i], i + 50);
    }
}
} // namespace rztl