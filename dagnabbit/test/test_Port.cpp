#include <memory>
#include <gtest/gtest.h>
#include "../Message.h"
#include "../Port.h"

using namespace dc;


TEST(Port, Basic) {
  Port::Config cfg;
  cfg.typeId = 5;
  cfg.prettyName = "Hiiiii";
  cfg.maxConnections = 8;
  Port port(cfg);
  ASSERT_EQ(port.typeId, cfg.typeId);
  ASSERT_EQ(port.prettyName, cfg.prettyName);
  ASSERT_EQ(port.maxConnections, cfg.maxConnections);

  // try to connect a port with the wrong type
  {
    Port::Config wrongCfg;
    wrongCfg.typeId = 8;
    Port wrongPort(wrongCfg);
    ASSERT_EQ(port.connect(&wrongPort), Status::TypeMismatch);
  }

  RTList<std::unique_ptr<Port>> otherPorts(cfg.maxConnections);
  // connect a bunch of ports
  for (size_t i = 0; i < cfg.maxConnections; ++i) {
    Port* newPort = new Port(cfg);
    otherPorts.add([newPort](std::unique_ptr<Port>& p) {
      p.reset(newPort);
    });
    const auto status = port.connect(newPort);
    ASSERT_EQ(status, Status::Ok);
  }
  ASSERT_EQ(port.getNumConnections(), cfg.maxConnections);

  // check disconnect
  {
    // disconnect a port that's connected
    Port* connectedPort;
    auto status = otherPorts.find(
        [](const std::unique_ptr<Port>&) { return true; },
        [&connectedPort](std::unique_ptr<Port>& p) { connectedPort = p.get(); });
    ASSERT_EQ(status, Status::Ok);
    status = port.disconnect(connectedPort);
    ASSERT_EQ(status, Status::Ok);
    ASSERT_EQ(port.getNumConnections(), cfg.maxConnections - 1);

    // try to disconnect the disconnected port from this one, should fail
    status = connectedPort->disconnect(&port);
    ASSERT_EQ(status, Status::NotFound);

    // try to disconnect a port that was never connected
    Port notConnectedPort(cfg);
    status = port.disconnect(&notConnectedPort);
    ASSERT_EQ(status, Status::NotFound);
  }

  // disconnect the rest and expect no connections
  const auto status = port.disconnectAll();
  ASSERT_EQ(status, Status::Ok);
  ASSERT_EQ(port.getNumConnections(), 0);

  // check that all the previously connected ports are disconnected from this one
  otherPorts.iterate([&port](std::unique_ptr<Port>& p) {
    ASSERT_FALSE(p->isConnectedTo(&port));
    ASSERT_FALSE(port.isConnectedTo(p.get()));
  });
}

TEST(Port, MessageQueueBasic) {
  using MessageType = Message<float, float>;
  using QueueType = SPSCQ<MessageType>;

  Port::Config cfg;
  cfg.createMessageQueueFn = []() {
    return new QueueType(16);
  };
  cfg.destroyMessageQueueFn = [](void* ptr) {
    auto q = static_cast<QueueType*>(ptr);
    delete q;
  };
  Port port(cfg);

  void* qPtr;
  ASSERT_EQ(port.getMessageQueue(qPtr), Status::Ok);

  auto q = static_cast<QueueType*>(qPtr);
  ASSERT_EQ(q->push([](MessageType& msg) {
    msg.data = 123.4f;
    return Status::Ok;
  }), Status::Ok);
  ASSERT_EQ(q->pop([](MessageType& msg) {
    return msg.data == 123.4f ? Status::Ok : Status::Fail;
  }), Status::Ok);
}
