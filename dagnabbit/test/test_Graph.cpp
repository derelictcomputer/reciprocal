#include <gtest/gtest.h>
#include "../Graph.h"
#include "../Message.h"

using namespace dc;

template<class DataType, class TimeType>
class PassthroughNode : public Node<TimeType> {
public:
  using MessageType = Message<DataType, TimeType>;
  using InputPortType = InputPort<MessageType>;
  using OutputPortType = OutputPort<MessageType>;

  PassthroughNode(size_t queueSize, size_t maxOutputConnections) :
      _input("in", queueSize),
      _output("out", maxOutputConnections) {
    // input
    this->_inputs.push_back(&_input);
    // output
    this->_outputs.push_back(&_output);
  }

  Status process(const TimeType&, const TimeType&) override {
    MessageType msg;
    while (popMessage(msg) == Status::Ok) {
      const auto status = _output.pushToConnections(msg);
      if (status != Status::Ok) {
        return status;
      }
    }
    return Status::Ok;
  }

  Status pushMessage(const MessageType& msg) {
    return _input.pushMessage(msg);
  }

  Status popMessage(MessageType& msg) {
    return _input.popMessage(msg);
  }

private:
  InputPortType _input;
  OutputPortType _output;
};

TEST(Graph, AddRemove) {
  using TimeType = double;
  const size_t asyncQueueSize = 32;
  const size_t maxNodes = 1024;

  Graph<TimeType> graph(asyncQueueSize, maxNodes);

  ASSERT_EQ(graph.capacity, maxNodes);
  ASSERT_EQ(graph.size(), 0);

  auto node = new PassthroughNode<int, TimeType>(1, 1);

  std::atomic<bool> gotCb{false};
  ASSERT_EQ(graph.addNode(node, [&gotCb](Status status, NodeId nodeId) {
    gotCb = true;
    ASSERT_EQ(status, Status::Ok);
    ASSERT_NE(nodeId, InvalidNodeId);
  }), Status::Ok);

  ASSERT_FALSE(gotCb);
  ASSERT_EQ(graph.size(), 0);

  ASSERT_EQ(graph.process(), Status::Ok);

  ASSERT_TRUE(gotCb);
  ASSERT_EQ(graph.size(), 1);
}
