#include <gtest/gtest.h>
#include "../Port.h"

using namespace dc;


TEST(Port, Basic) {
  const PortTypeId portTypeId = 5;
  const size_t maxConnections = 8;
  Port port(maxConnections);
  ASSERT_EQ(port.typeId, InvalidPortType);
  ASSERT_EQ(port.prettyName, "");
  for (size_t i = 0; i < maxConnections; ++i) {
    const auto status = port.connections.add([](Port*& newPort) {
      newPort = new Port(maxConnections);
      newPort->typeId = portTypeId;
    });
    ASSERT_EQ(status, Status::Ok);
  }
  const auto status = port.connections.clear([portTypeId](Port*& existingPort) {
    ASSERT_EQ(existingPort->typeId, portTypeId);
    delete existingPort;
  });
  ASSERT_EQ(status, Status::Ok);
  size_t numConnections;
  ASSERT_EQ(port.connections.size(numConnections), Status::Ok);
  ASSERT_EQ(numConnections, 0);
}
