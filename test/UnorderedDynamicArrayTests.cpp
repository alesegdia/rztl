#include <gtest/gtest.h>
#include "rztl/unordereddynamicarray.h"

namespace rztl {

    TEST(UnorderedDynamicArrayTest, DefaultConstructor) {
        UnorderedDynamicArray<int> arr;
        EXPECT_EQ(arr.GetSize(), 0);
    }

    TEST(UnorderedDynamicArrayTest, ParameterizedConstructor) {
        UnorderedDynamicArray<int> arr(10);
        EXPECT_EQ(arr.GetSize(), 0);
        EXPECT_EQ(arr.GetCapacity(), 10);
    }

    TEST(UnorderedDynamicArrayTest, AddElement) {
        UnorderedDynamicArray<int> arr;
        arr.Add(5);
        EXPECT_EQ(arr.GetSize(), 1);
        EXPECT_EQ(arr[0], 5);
    }

    TEST(UnorderedDynamicArrayTest, AddMultipleElements) {
        UnorderedDynamicArray<int> arr;
        for (int i = 0; i < 100; ++i) {
            arr.Add(i);
        }
        EXPECT_EQ(arr.GetSize(), 100);
        for (int i = 0; i < 100; ++i) {
            EXPECT_EQ(arr[i], i);
        }
    }

    TEST(UnorderedDynamicArrayTest, AddElementWithRealloc) {
        UnorderedDynamicArray<int> arr(2, 5);
        arr.Add(1);
        arr.Add(2);
        arr.Add(3);
        EXPECT_EQ(arr.GetSize(), 3);
        EXPECT_EQ(arr.GetCapacity(), 7);
        EXPECT_EQ(arr[2], 3);
    }

    TEST(UnorderedDynamicArrayTest, GetBackElement) {
        UnorderedDynamicArray<int> arr;
        arr.Add(5);
        arr.Add(10);
        EXPECT_EQ(arr.GetBackElement(), 10);
    }

    TEST(UnorderedDynamicArrayTest, Clear) {
        UnorderedDynamicArray<int> arr;
        arr.Add(5);
        arr.Add(10);
        arr.Clear();
        EXPECT_EQ(arr.GetSize(), 0);
    }

    TEST(UnorderedDynamicArrayTest, RemoveBackElement) {
        UnorderedDynamicArray<int> arr;
        arr.Add(5);
        arr.Add(10);
        arr.RemoveBackElement();
        EXPECT_EQ(arr.GetSize(), 1);
        EXPECT_EQ(arr.GetBackElement(), 5);
    }

    TEST(UnorderedDynamicArrayTest, RemoveMultipleBackElements) {
        UnorderedDynamicArray<int> arr;
        for (int i = 0; i < 100; ++i) {
            arr.Add(i);
        }
        for (int i = 0; i < 50; ++i) {
            arr.RemoveBackElement();
        }
        EXPECT_EQ(arr.GetSize(), 50);
        for (int i = 0; i < 50; ++i) {
            EXPECT_EQ(arr[i], i);
        }
    }

    TEST(UnorderedDynamicArrayTest, IsEmpty) {
        UnorderedDynamicArray<int> arr;
        EXPECT_TRUE(arr.IsEmpty());
        arr.Add(5);
        EXPECT_FALSE(arr.IsEmpty());
    }

    TEST(UnorderedDynamicArrayTest, GetRawData) {
        UnorderedDynamicArray<int> arr;
        arr.Add(5);
        arr.Add(10);
        int* rawData = arr.GetRawData();
        EXPECT_EQ(rawData[0], 5);
        EXPECT_EQ(rawData[1], 10);
    }

    TEST(UnorderedDynamicArrayTest, RemoveIndex) {
        UnorderedDynamicArray<int> arr;
        for (int i = 0; i < 10; ++i) {
            arr.Add(i);
        }
        arr.removeIndex(5);
        EXPECT_EQ(arr.GetSize(), 9);
        EXPECT_EQ(arr[5], 9); // Last element should be moved to index 5
    }

    TEST(UnorderedDynamicArrayTest, RemoveElement) {
        UnorderedDynamicArray<int> arr;
        for (int i = 0; i < 10; ++i) {
            arr.Add(i);
        }
        arr.remove(5);
        EXPECT_EQ(arr.GetSize(), 9);
        EXPECT_EQ(arr[5], 9); // Last element should be moved to index 5
    }

}