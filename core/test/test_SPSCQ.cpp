#include <thread>
#include <gtest/gtest.h>
#include "../SPSCQ.h"

using namespace dc;

TEST(SPSCQ, Capacity) {
  ASSERT_EQ(SPSCQ<int>(512).capacity, 512);
  ASSERT_EQ(SPSCQ<int>(511).capacity, 512);
  ASSERT_EQ(SPSCQ<int>(513).capacity, 1024);
}

TEST(SPSCQ, PushPopCount) {
  struct Thing {
    size_t val1{0};
    float val2{0};
  };

  const size_t capacity = 1024;
  SPSCQ<Thing> q(capacity);
  ASSERT_EQ(q.capacity, capacity);
  ASSERT_EQ(q.size(), 0);

  const Thing expectedThing{5432, 67.234f};

  // push a bunch of items
  std::atomic<size_t> numPushed{0};
  std::thread pushThread([&q, &numPushed, &expectedThing]() {
    Status status;
    do {
      std::this_thread::yield();
      status = q.push(expectedThing);
    } while (status == Status::Ok && numPushed.fetch_add(1) < capacity);
  });

  // wait until we've pushed all we're going to push
  while (numPushed < capacity) {
    Thing actualThing{};
    const auto status = q.pop(actualThing);
    ASSERT_TRUE(status == Status::Ok || status == Status::Empty);
    if (status == Status::Ok) {
      ASSERT_EQ(expectedThing.val1, actualThing.val1);
      ASSERT_FLOAT_EQ(expectedThing.val2, actualThing.val2);
    }
    std::this_thread::yield();
  }
  pushThread.join();

  // now push until full and expect to hit Status::Full
  while (true) {
    const auto status = q.push(expectedThing);
    if (status == Status::Full) {
      break;
    }
    ASSERT_EQ(status, Status::Ok);
  }
  ASSERT_EQ(q.size(), q.capacity);

  // now pop until empty and expect to hit Status::Empty
  while (true) {
    Thing actualThing{};
    const auto status = q.pop(actualThing);
    if (status == Status::Empty) {
      break;
    }
    ASSERT_EQ(status, Status::Ok);
  }
  ASSERT_EQ(q.size(), 0);
}
