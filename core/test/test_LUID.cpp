#include <gtest/gtest.h>
#include "../LUID.h"

using namespace dc;

using TestTypes = ::testing::Types<uint8_t, uint16_t, int, size_t>;
template <class T>
class LUIDTest : public ::testing::Test {};
TYPED_TEST_SUITE(LUIDTest, TestTypes, );

TYPED_TEST(LUIDTest, NoMax) {
  LUID<TypeParam> luid;

  std::vector<TypeParam> ids;

  // get some ids
  for (size_t i = 0; i < 16; ++i) {
    TypeParam id;
    ASSERT_EQ(luid.get(id), Status::Ok);
    ids.push_back(id);
  }

  // make sure there are no duplicates
  for (size_t i = 0; i < ids.size(); ++i) {
    for (size_t j = 0; j < ids.size(); ++j) {
      if (i == j) {
        continue;
      }
      ASSERT_NE(ids[i], ids[j]);
    }
  }

  // put them all back
  for (auto id : ids) {
    ASSERT_EQ(luid.replace(id), Status::Ok);
  }

  // try to put back an id we already put back
  ASSERT_EQ(luid.replace(ids[0]), Status::Duplicate);
}

TYPED_TEST(LUIDTest, Max) {
  const size_t maxSize = 32;
  LUID<TypeParam, maxSize> luid;

  std::vector<TypeParam> ids;

  // get all the ids
  for (size_t i = 0; i < maxSize; ++i) {
    TypeParam id;
    ASSERT_EQ(luid.get(id), Status::Ok);
    ids.push_back(id);
  }

  // try to get another
  {
    TypeParam id;
    ASSERT_EQ(luid.get(id), Status::Empty);
  }

  // make sure there are no duplicates
  for (size_t i = 0; i < ids.size(); ++i) {
    for (size_t j = 0; j < ids.size(); ++j) {
      if (i == j) {
        continue;
      }
      ASSERT_NE(ids[i], ids[j]);
    }
  }

  // put them all back
  for (auto id : ids) {
    ASSERT_EQ(luid.replace(id), Status::Ok);
  }

  // try to put back an id we already put back
  ASSERT_EQ(luid.replace(ids[0]), Status::Duplicate);
}
