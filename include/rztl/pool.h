#pragma once

#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <vector>

namespace rztl
{

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

    public:
        static constexpr uint16_t kPageSize = 4096;
        static constexpr uint16_t kNumItemsPerBlock = kPageSize / sizeof(Item);

		struct PoolBlock {
			PoolBlock()
            {
				for (size_t i = 0; i < kNumItemsPerBlock; i++)
				{
                    blockData[i].state.next = (i < kNumItemsPerBlock - 1) ? &blockData[i + 1] : nullptr;
				}
            }
			Item blockData[kNumItemsPerBlock];
		};


    public:

        Pool()
		{
			mFreeFirst = nullptr;
			mFreeLast = nullptr;
			AllocBlock();
		}

        ~Pool() {
            Clear();
        }

        template <typename...ARGS>
        T* Create(ARGS&&...args)
        {
            if (mFreeFirst->state.next == nullptr)
            {
                AllocBlock();
            }

            Item* item = mFreeFirst;
            mFreeFirst = mFreeFirst->state.next;

            T* obj = new(&item->obj_data) T(std::forward<ARGS>(args)...);

            mNumItemsInUse++;
            return obj;
        }

        /*
         * Llama al destructor del objeto y asigna el mFreeFirst
         */
        void Destroy(T* e)
        {
            e->~T();
            mFreeLast->state.next = (Item*)e;
            mFreeLast = (Item*)e;
            mFreeLast->state.next = nullptr;
            mNumItemsInUse--;
        }

        // possible improvement: don't clear mBlockList, but then we need to take care
        // about properly linking one block with another
        void Clear()
        {
            // go through all the blocks, and for each item, if it's in use, call teh destructor
			for (auto block : mBlockList)
			{
				for (size_t i = 0; i < kNumItemsPerBlock; i++)
				{
					if (block.blockData[i].state.in_use)
					{
						block.blockData[i].obj_data.~T();
					}
				}
			}

            mFreeFirst = nullptr;
            mFreeLast = nullptr;
            mNumItemsInUse = 0;
            mBlockList.clear();
			AllocBlock();
        }

        size_t GetSize() const {
            return mNumItemsInUse;
        }

        size_t GetBlockListCount() const {
            return mBlockList.size();
        }

        size_t GetTotalAllocatedMemory() const {
            return mBlockList.size() * kNumItemsPerBlock * sizeof(Item);
        }

        size_t GetUsedMemory() const {
            return mNumItemsInUse * sizeof(T);
        }

		size_t GetNumItemsPerBlock() const {
			return kNumItemsPerBlock;
		}

        private:
            Item* mFreeFirst;
            Item* mFreeLast;
            std::vector<PoolBlock> mBlockList;

            size_t mNumItemsInUse = 0;

            void AllocBlock()
            {
                mBlockList.emplace_back();
				auto newBlock = mBlockList.back();
                mFreeFirst = newBlock.blockData;
                mFreeLast = newBlock.blockData + kNumItemsPerBlock - 1;
            }

    };

}