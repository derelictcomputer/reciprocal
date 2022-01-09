#include <atomic>
#include <memory>
#include <thread>
#include <vector>
#include <gtest/gtest.h>
#include "../LFPool.h"

using namespace dc;

TEST(LFPool, AcquireRelease) {
  struct Stuff {
    size_t numThings;
    std::unique_ptr<float[]> things;

    Stuff(size_t numThings, float initialThingsValue) : numThings(numThings), things(new float[numThings]) {
      for (size_t i = 0; i < numThings; ++i) {
        things[i] = initialThingsValue;
      }
    }
  };

  const size_t poolSize = 64;
  const size_t numThings = 9;
  const float initialValue = 234.5f;
  LFPool<Stuff> pool(poolSize, numThings, initialValue);

  // make sure we can't add another item to a full pool
  {
    Stuff extraStuff(3, 234.234f);
    ASSERT_EQ(pool.release(&extraStuff), Status::Full);
  }

  // acquire all the stuff
  std::vector<Stuff*> acquiredStuff;
  for (size_t i = 0; i < poolSize; ++i) {
    Stuff* stuffPtr{nullptr};
    ASSERT_EQ(pool.acquire(stuffPtr), Status::Ok);
    ASSERT_NE(stuffPtr, nullptr);
    ASSERT_EQ(stuffPtr->numThings, numThings);
    for (size_t j = 0; j < numThings; ++j) {
      ASSERT_FLOAT_EQ(stuffPtr->things[j], initialValue);
    }
    acquiredStuff.push_back(stuffPtr);
  }

  // try to get one more, should fail
  {
    Stuff* stuffPtr{nullptr};
    ASSERT_EQ(pool.acquire(stuffPtr), Status::Empty);
    ASSERT_EQ(stuffPtr, nullptr);
  }

  // put the stuff back, we don't want more stuff anyway
  for (size_t i = 0; i < poolSize; ++i) {
    ASSERT_NE(acquiredStuff[i], nullptr);
    ASSERT_EQ(pool.release(acquiredStuff[i]), Status::Ok);
  }
}

TEST(LFPool, MTAcquireRelease) {
  const size_t poolSize = 128;
  const int expectedValue = 876;
  LFPool<int> pool(poolSize, expectedValue);

  std::atomic<size_t> numAcquired{0};

  const size_t numThreads = 13;
  std::vector<std::thread> threads;
  for (size_t i = 0; i < numThreads; ++i) {
    threads.emplace_back([expectedValue, &numAcquired, &pool]() {
      std::vector<int*> acquired;
      while (numAcquired.load() < poolSize) {
        int* p{nullptr};
        const auto status = pool.acquire(p);
        if (status == Status::Ok) {
          ASSERT_NE(p, nullptr);
          ASSERT_EQ(*p, expectedValue);
          acquired.push_back(p);
          numAcquired.fetch_add(1);
        }
        else {
          ASSERT_EQ(p, nullptr);
        }
        std::this_thread::yield();
      }

      for (auto p : acquired) {
        ASSERT_EQ(pool.release(p), Status::Ok);
        std::this_thread::yield();
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  ASSERT_EQ(numAcquired, poolSize);
}
