#include <gtest/gtest.h>
#include "../Message.h"
#include "../Status.h"

using namespace dc;

template<class DataType, size_t DataSize>
void basicTest() {
  Message<DataType, DataSize> msg;
  ASSERT_EQ(msg.typeId, InvalidMessageTypeId);
  ASSERT_EQ(msg.dataSize, DataSize);
}

TEST(Message, Basic) {
  basicTest<float, 3>();
  basicTest<double, 9>();
  basicTest<uint64_t, 2>();
}
