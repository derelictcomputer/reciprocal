#include <gtest/gtest.h>
#include "../Message.h"
#include "../../core/Status.h"

using namespace dc;

template<class DataType, class TimeType>
void basicTest() {
  using MessageType = Message<DataType, TimeType>;
  MessageType msg;
  msg.time = TimeType();
  msg.data = DataType();
}

TEST(Message, Basic) {
  basicTest<float, size_t>();
  basicTest<double, float>();
  basicTest<uint64_t, double>();
}
