#include <memory>
#include <thread>
#include <gtest/gtest.h>
#include "../../core/SPSCQ.h"
#include "../Message.h"
#include "../Port.h"

using namespace dc;


TEST(Port, Basic) {
  IPort::Config cfg;
  cfg.typeId = 5;
  cfg.prettyName = "Hiiiii";
  cfg.maxConnections = 8;
  IPort port(cfg);
  ASSERT_EQ(port.typeId, cfg.typeId);
  ASSERT_EQ(port.prettyName, cfg.prettyName);
  ASSERT_EQ(port.maxConnections, cfg.maxConnections);

  // try to connect a port with the wrong type
  {
    IPort::Config wrongCfg;
    wrongCfg.typeId = 8;
    IPort wrongPort(wrongCfg);
    ASSERT_EQ(port.connect(&wrongPort), Status::TypeMismatch);
  }

  std::vector<std::unique_ptr<IPort>> otherPorts;
  // connect a bunch of ports
  for (size_t i = 0; i < cfg.maxConnections; ++i) {
    otherPorts.push_back(std::make_unique<IPort>(cfg));
    const auto status = port.connect(otherPorts[i].get());
    ASSERT_EQ(status, Status::Ok);
  }
  ASSERT_EQ(port.getNumConnections(), cfg.maxConnections);

  // check disconnect
  {
    // disconnect a port that's connected
    auto status = port.disconnect(otherPorts[0].get());
    ASSERT_EQ(status, Status::Ok) << to_string(status);
    ASSERT_EQ(port.getNumConnections(), cfg.maxConnections - 1);

    // try to disconnect the disconnected port from this one, should fail
    status = otherPorts[0]->disconnect(&port);
    ASSERT_EQ(status, Status::NotFound);

    // try to disconnect a port that was never connected
    IPort notConnectedPort(cfg);
    status = port.disconnect(&notConnectedPort);
    ASSERT_EQ(status, Status::NotFound);
  }

  // disconnect the rest and expect no connections
  const auto status = port.disconnectAll();
  ASSERT_EQ(status, Status::Ok);
  ASSERT_EQ(port.getNumConnections(), 0);

  // check that all the previously connected ports are disconnected from this one
  for (size_t i = 1; i < otherPorts.size(); ++i) {
    ASSERT_FALSE(otherPorts[i]->isConnectedTo(&port));
    ASSERT_FALSE(port.isConnectedTo(otherPorts[i].get()));
  }
}

TEST(Port, MessageQueueBasic) {
  using MessageType = Message<float, float>;

  IPort::Config cfg;
  InputPort<MessageType> port(cfg, 32);

  MessageType msgIn;
  msgIn.data = 123.4f;
  msgIn.time = 432.1f;
  ASSERT_EQ(port.pushMessage(msgIn), Status::Ok);

  MessageType msgOut;
  ASSERT_EQ(port.popMessage(msgOut), Status::Ok);
  ASSERT_FLOAT_EQ(msgIn.data, msgOut.data);
  ASSERT_FLOAT_EQ(msgIn.time, msgOut.time);
}

TEST(Port, MTConnections) {
  using MessageType = Message<int, size_t>;

  IPort::Config cfg;
  cfg.typeId = 5;
  cfg.maxConnections = 1;

  InputPort<MessageType> inPort(cfg, 16);
  OutputPort<MessageType> outPort(cfg);

  // one thread connects and disconnects while the other pushes messages to the output node's connections
  std::atomic<bool> run{true};
  std::thread connectThread([&run, &inPort, &outPort]() {
    while (run.load()) {
      ASSERT_EQ(outPort.connect(&inPort), Status::Ok);
      std::this_thread::yield();
      ASSERT_EQ(inPort.disconnect(&outPort), Status::Ok);
      std::this_thread::yield();
    }
  });
  for (size_t i = 0; i < 1000; ++i) {
    MessageType msg;
    ASSERT_EQ(outPort.pushToConnections(msg), Status::Ok);
    std::this_thread::yield();
    inPort.popMessage(msg); // this can fail if the nodes weren't connected, and that's ok.
  }
  run = false;
  connectThread.join();
}
