#include <gtest/gtest.h>
#include "../RTList.h"

using namespace dc;

TEST(RTList, Add) {
  const size_t size = 123;
  RTList<int> list(size);

  // check initial size
  ASSERT_EQ(list.size(), 0);

  // fill up the list and expect the size to increase
  for (size_t i = 0; i < size; ++i) {
    const auto status = list.add([i](int& val) {
      val = static_cast<int>(i);
    });
    ASSERT_EQ(status, Status::Ok);
    ASSERT_EQ(list.size(), i + 1);
  }
}

TEST(RTList, Iterate) {
  const size_t size = 153;
  RTList<int> list(size);

  // fill up the list and expect the size to increase
  for (size_t i = 0; i < size; ++i) {
    auto status = list.add([i](int& val) {
      val = static_cast<int>(i);
    });
    ASSERT_EQ(status, Status::Ok);
    ASSERT_EQ(list.size(), i + 1);
  }

  // check the values, expect them to be increasing from zero
  int i{0};
  auto status = list.iterate([&i](int& val) {
    ASSERT_EQ(val, i++);
  });
  ASSERT_EQ(status, Status::Ok);
}

TEST(RTList, Find) {
  const size_t size = 542;
  RTList<int> list(size);

  // add an item, then try to find it
  const int expectedVal = 2345;
  bool found{false};
  auto status = list.add([](int& val) {
    val = expectedVal;
  });
  ASSERT_EQ(status, Status::Ok);
  status = list.find(
      [](const int& val) {
        return val == expectedVal;
      },
      [&found](int&) {
        found = true;
      });
  ASSERT_EQ(status, Status::Ok);
  ASSERT_TRUE(found);
}

TEST(RTList, Remove) {
  const size_t size{678};
  RTList<int> list(size);

  // add an item, then try to remove it
  const int expectedVal = 2345;
  bool removed{false};
  auto status = list.add([](int& val) {
    val = expectedVal;
  });
  ASSERT_EQ(status, Status::Ok);
  status = list.remove(
      [](const int& val) {
        return val == expectedVal;
      },
      [&removed](int&) {
        removed = true;
      });
  ASSERT_EQ(status, Status::Ok);
  ASSERT_TRUE(removed);

  ASSERT_EQ(list.size(), 0);
}

TEST(RTList, RemoveAll) {
  const size_t size = 153;
  RTList<int> list(size);

  // fill up the list and expect the size to increase
  for (size_t i = 0; i < size; ++i) {
    auto status = list.add([i](int& val) {
      val = static_cast<int>(i);
    });
    ASSERT_EQ(status, Status::Ok);
    ASSERT_EQ(list.size(), i + 1);
  }

  // remove all the odd numbered items
  const size_t expectedRemoved = size / 2;
  size_t actualRemoved{0};
  auto status = list.removeAll(
      [](const int& val) {
        return val % 2 != 0;
      },
      [&actualRemoved](int&) {
        ++actualRemoved;
      });
  ASSERT_EQ(status, Status::Ok);
  ASSERT_EQ(actualRemoved, expectedRemoved);
  ASSERT_EQ(list.size(), size - expectedRemoved);
}

TEST(RTList, Clear) {
  const size_t size = 153;
  RTList<int> list(size);

  // fill up the list and expect the size to increase
  for (size_t i = 0; i < size; ++i) {
    auto status = list.add([i](int& val) {
      val = static_cast<int>(i);
    });
    ASSERT_EQ(status, Status::Ok);
    ASSERT_EQ(list.size(), i + 1);
  }

  // clear, expect empty
  auto status = list.clear([](int&) {});
  ASSERT_EQ(status, Status::Ok);
  ASSERT_EQ(list.size(), 0);
}
