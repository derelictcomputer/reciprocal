#include <gtest/gtest.h>
#include "../Port.h"

using namespace dc;

template<class DataType, size_t DataSize, class TimeType, PortTypeId TypeId>
void basicTest(const std::string& portName) {
  const size_t queueSize = 256;
  using PortType = Port<DataType, DataSize, TimeType, TypeId>;
  PortType port(queueSize);
  ASSERT_EQ(port.typeId, TypeId);
  port.prettyName = portName;
  ASSERT_EQ(port.prettyName, portName);
  using MessageType = Message<DataType, DataSize, TimeType>;
  for (size_t i = 0; i < queueSize; ++i) {
    ASSERT_EQ(port.messageQueue.push([](MessageType&) { return Status::Ok; }), Status::Ok);
  }
  ASSERT_EQ(port.messageQueue.push([](MessageType&) { return Status::Ok; }), Status::Full);
  while (port.messageQueue.size() > 0) {
    ASSERT_EQ(port.messageQueue.pop([](const MessageType&) { return Status::Ok; }), Status::Ok);
  }
  ASSERT_EQ(port.messageQueue.pop([](const MessageType&) { return Status::Ok; }), Status::Empty);
}

TEST(Port, Basic) {
  basicTest<float, 3, size_t, 0>("Yes?");
  basicTest<double, 9, float, 3>("No.");
  basicTest<uint64_t, 2, double, 42>("Perhaps?");
}
