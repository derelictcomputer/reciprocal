#include <memory>
#include <thread>
#include <gtest/gtest.h>
#include "../../core/SPSCQ.h"
#include "../Message.h"
#include "../Port.h"

using namespace dc;


TEST(Port, Basic) {
  using MessageType = Message<size_t, double>;
  const std::string prettyName = "Hiiiiii";
  const size_t maxConnections = 8;
  OutputPort<MessageType> port(prettyName, maxConnections);
  ASSERT_EQ(port.prettyName, prettyName);
  ASSERT_EQ(port.maxConnections, maxConnections);

  // Try to connect a port of the wrong type
  {
    InputPort<Message<char, double>> wrongPort("wrooonnnng", 2);
    ASSERT_EQ(port.connect(&wrongPort), Status::TypeMismatch);
  }

  std::vector<std::unique_ptr<InputPort<MessageType>>> otherPorts;
  // connect a bunch of ports
  for (size_t i = 0; i < maxConnections; ++i) {
    otherPorts.push_back(std::make_unique<InputPort<MessageType>>("asdf", 16));
    const auto status = otherPorts[i]->connect(&port);
    ASSERT_EQ(status, Status::Ok);
  }
  ASSERT_EQ(port.getNumConnections(), maxConnections);

  // check disconnect
  {
    // disconnect a port that's connected
    auto status = otherPorts[0]->disconnect(&port);
    ASSERT_EQ(status, Status::Ok) << to_string(status);
    ASSERT_EQ(port.getNumConnections(), maxConnections - 1);

    // try to disconnect again, should fail
    status = otherPorts[0]->disconnect(&port);
    ASSERT_EQ(status, Status::NotFound);

    // try to disconnect a port that was never connected
    InputPort<MessageType> notConnectedPort("asdffadsfasd", 12);
    status = notConnectedPort.disconnect(&port);
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

  InputPort<MessageType> port("qwerqwer", 32);

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

  InputPort<MessageType> inPort("In", 16);
  OutputPort<MessageType> outPort("Out", 1);

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
