#include <gtest/gtest.h>
#include "../Message.h"
#include "../../core/Status.h"

using namespace dc;

template<class DataType, size_t DataSize, class TimeType>
void basicTest() {
  using MessageType = Message<DataType, DataSize, TimeType>;
  MessageType msg;
  ASSERT_EQ(msg.dataSize, DataSize);
  for (size_t i = 0; i < DataSize; ++i) {
    msg.data[i] = DataType(i);
  }
}

TEST(Message, Basic) {
  basicTest<float, 3, size_t>();
  basicTest<double, 9, float>();
  basicTest<uint64_t, 2, double>();
}
