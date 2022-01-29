#include <gtest/gtest.h>
#include "../TrashMan.h"

using namespace dc;

struct TestThing {
  int a;
  float b;
  TestThing* c;
};

// This test will check that the initial size and capacity are zero,
// lsan will tell us if TrashMan leaks memory.
TEST(TrashMan, Simple) {
  const size_t capacity = 1024;
  TrashMan<TestThing> trashMan(capacity);

  ASSERT_EQ(trashMan.capacity(), capacity);
  ASSERT_EQ(trashMan.size(), 0);

  for (size_t i = 0; i < capacity; ++i) {
    auto thing = new TestThing{1, 2.0f, nullptr};
    ASSERT_EQ(trashMan.trash(thing), Status::Ok);
    ASSERT_EQ(thing, nullptr);
  }
}
