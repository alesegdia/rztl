#include <gtest/gtest.h>
#include "rztl/pool.h"

namespace rztl {

    class TestObject {
    public:
        uint64_t value;
        TestObject() : value(0) {}
        TestObject(uint64_t v) : value(v) {}
    };

    TEST(PoolTest, DefaultConstructor) {
        Pool<TestObject> pool;
        EXPECT_EQ(pool.GetSize(), 0);
        EXPECT_EQ(pool.GetBlockListCount(), 1);
        EXPECT_EQ(pool.GetTotalAllocatedMemory(), Pool<TestObject>::kPageSize);
        EXPECT_EQ(pool.GetUsedMemory(), 0);
    }

    TEST(PoolTest, AllocateAndDeallocate) {
        Pool<TestObject> pool;
        TestObject* obj = pool.Create();
        EXPECT_NE(obj, nullptr);
        EXPECT_EQ(pool.GetSize(), 1);
        EXPECT_EQ(pool.GetUsedMemory(), sizeof(TestObject));
        pool.Destroy(obj);
        EXPECT_EQ(pool.GetSize(), 0);
        EXPECT_EQ(pool.GetUsedMemory(), 0);
    }

    TEST(PoolTest, AllocateMultiple) {
        Pool<TestObject> pool;
        TestObject* obj1 = pool.Create();
        TestObject* obj2 = pool.Create();
        EXPECT_NE(obj1, nullptr);
        EXPECT_NE(obj2, nullptr);
        EXPECT_EQ(pool.GetSize(), 2);
        EXPECT_EQ(pool.GetUsedMemory(), 2 * sizeof(TestObject));
        pool.Destroy(obj1);
        pool.Destroy(obj2);
        EXPECT_EQ(pool.GetSize(), 0);
        EXPECT_EQ(pool.GetUsedMemory(), 0);
    }

    TEST(PoolTest, ReuseDeallocated) {
        Pool<TestObject> pool;

        TestObject* firstObj = nullptr;
        for (int i = 0; i < pool.GetNumItemsPerBlock() - 2; i++)
        {
            TestObject* obj = pool.Create(i);
            if (firstObj == nullptr)
            {
                firstObj = obj;
            }
        }

        EXPECT_EQ(pool.GetSize(), pool.GetNumItemsPerBlock() - 1);
        EXPECT_EQ(pool.GetBlockListCount(), 1);

        pool.Destroy(firstObj);

        TestObject* lastObject = pool.Create(0xDEADBEEF);
        EXPECT_EQ(firstObj, lastObject); // Should reuse the same memory
    }

    TEST(PoolTest, AllocateWithConstructor) {
        Pool<TestObject> pool;
        TestObject* obj = pool.Create(42);
        EXPECT_NE(obj, nullptr);
        EXPECT_EQ(obj->value, 42);
        pool.Destroy(obj);
    }

    TEST(PoolTest, Clear) {
        Pool<TestObject> pool;
        pool.Create();
        pool.Create();
        EXPECT_EQ(pool.GetSize(), 2);
        pool.Clear();
        EXPECT_EQ(pool.GetSize(), 0);
        EXPECT_EQ(pool.GetUsedMemory(), 0);
    }

    TEST(PoolTest, BlockAllocation) {
        Pool<TestObject> pool;
        size_t initialBlockCount = pool.GetBlockListCount();
        size_t initialTotalMemory = pool.GetTotalAllocatedMemory();

        // Allocate enough objects to require a new block
        for (size_t i = 0; i < pool.GetNumItemsPerBlock() + 1; ++i) {
            pool.Create();
        }

        EXPECT_GT(pool.GetBlockListCount(), initialBlockCount);
        EXPECT_GT(pool.GetTotalAllocatedMemory(), initialTotalMemory);
    }

    TEST(PoolTest, MemoryUsage) {
        Pool<TestObject> pool;
        size_t initialUsedMemory = pool.GetUsedMemory();

        TestObject* obj1 = pool.Create();
        TestObject* obj2 = pool.Create(42);

        EXPECT_EQ(pool.GetUsedMemory(), initialUsedMemory + 2 * sizeof(TestObject));

        pool.Destroy(obj1);
        pool.Destroy(obj2);

        EXPECT_EQ(pool.GetUsedMemory(), initialUsedMemory);
    }
    TEST(PoolTest, MemoryUsageAfterClearAndReuse) {

        Pool<TestObject> pool;
        {
            static constexpr size_t kNumBlocks = 3;

            const size_t numElements = pool.GetNumItemsPerBlock() * kNumBlocks - kNumBlocks;

            // Fill the pool to require multiple blocks
            for (size_t i = 0; i < numElements; ++i) {
                pool.Create(i);
            }

            EXPECT_EQ(pool.GetSize(), numElements);
            EXPECT_EQ(pool.GetUsedMemory(), numElements * sizeof(TestObject));
            EXPECT_EQ(pool.GetBlockListCount(), kNumBlocks);
            EXPECT_EQ(pool.GetTotalAllocatedMemory(), kNumBlocks * Pool<TestObject>::kPageSize);

            // Clear the pool and check memory usage
            pool.Clear();
            EXPECT_EQ(pool.GetSize(), 0);
            EXPECT_EQ(pool.GetUsedMemory(), 0);
            EXPECT_GT(pool.GetBlockListCount(), 1); // just one empty block is left
            EXPECT_GT(pool.GetTotalAllocatedMemory(), Pool<TestObject>::kPageSize);
        }

        {
            static constexpr size_t kNumBlocks = 5;

            const size_t numElements = pool.GetNumItemsPerBlock() * kNumBlocks - kNumBlocks;

            // Fill the pool to require multiple blocks
            for (size_t i = 0; i < numElements; ++i) {
                pool.Create(i);
            }

            EXPECT_EQ(pool.GetSize(), numElements);
            EXPECT_EQ(pool.GetUsedMemory(), numElements * sizeof(TestObject));
            EXPECT_EQ(pool.GetBlockListCount(), kNumBlocks);
            EXPECT_EQ(pool.GetTotalAllocatedMemory(), kNumBlocks * Pool<TestObject>::kPageSize);

            // Clear the pool and check memory usage
            pool.Clear();
            EXPECT_EQ(pool.GetSize(), 0);
            EXPECT_EQ(pool.GetUsedMemory(), 0);
            EXPECT_EQ(pool.GetBlockListCount(), 1); // just one empty block is left
            EXPECT_EQ(pool.GetTotalAllocatedMemory(), Pool<TestObject>::kPageSize);
        }

    }


} // namespace rztl