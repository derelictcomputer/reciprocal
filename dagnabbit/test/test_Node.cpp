#include <gtest/gtest.h>
#include <memory>
#include "../Node.h"

using namespace dc;

TEST(Node, Proc) {
  size_t numProcessCalls{0};
  Node::Config cfg;
  cfg.processFn = [&numProcessCalls](Node &node) -> Status {
    ++numProcessCalls;
    return Status::Ok;
  };
  Node node(cfg);
  ASSERT_EQ(node.process(), Status::Ok);
  ASSERT_EQ(numProcessCalls, 1);
}

TEST(Node, Params) {
  const size_t numParams = 5;
  Node::Config cfg;
  for (size_t i = 0; i < numParams; ++i) {
    const float min = i;
    const float max = i + 10.0f;
    const float def = (max - min) / 2.0f;
    const float step = 10.0f / (i + 1);
    cfg.params.push_back(Param({min, max, def, step}));
  }

  Node node(cfg);
  ASSERT_EQ(node.numParams(), numParams);

  for (size_t i = 0; i < numParams; ++i) {
    const float min = i;
    const float max = i + 10.0f;
    const float def = (max - min) / 2.0f;
    const float step = 10.0f / (i + 1);
    // check default
    float v;
    ASSERT_EQ(node.getParam(i, v), Status::Ok);
    EXPECT_FLOAT_EQ(v, def);
    // check clamp
    ASSERT_EQ(node.setParam(i, min - step), Status::Ok);
    ASSERT_EQ(node.getParam(i, v), Status::Ok);
    EXPECT_FLOAT_EQ(v, min);
    ASSERT_EQ(node.setParam(i, max + step), Status::Ok);
    ASSERT_EQ(node.getParam(i, v), Status::Ok);
    EXPECT_FLOAT_EQ(v, max);
    // check snap
    ASSERT_EQ(node.setParam(i, min + step * 0.4f), Status::Ok);
    ASSERT_EQ(node.getParam(i, v), Status::Ok);
    EXPECT_FLOAT_EQ(v, min);
  }
}

TEST(Node, Ports) {
  Node::Config cfg;
  // make some different-sized ports, but make the inputs and outputs match
  const size_t numPorts = 10;
  std::vector<std::unique_ptr<float[]>> buffers;
  for (auto i = 0; i < numPorts; ++i) {
    const size_t numSamples = i * 2 + 64;
    const size_t numChannels = i + 1;
    buffers.push_back(std::make_unique<float[]>(numSamples * numChannels));
    cfg.inputPorts.push_back({buffers[i].get(), numSamples, numChannels});
    cfg.outputPorts.push_back({nullptr, numSamples, numChannels});
  }
  // make the node
  Node node(cfg);

  // process and expect to see the inputs passed through to the outputs
  ASSERT_EQ(node.process(), Status::Ok);
  size_t nodeNumPorts;
  ASSERT_EQ(node.getNumPorts(Node::PortType::Input, nodeNumPorts), Status::Ok);
  ASSERT_EQ(nodeNumPorts, numPorts);
  for (auto i = 0; i < numPorts; ++i) {
    Port *inPort{nullptr};
    ASSERT_EQ(node.getPort(i, Node::PortType::Input, inPort), Status::Ok);
    ASSERT_NE(inPort, nullptr);
    Port *outPort{nullptr};
    ASSERT_EQ(node.getPort(i, Node::PortType::Output, outPort), Status::Ok);
    ASSERT_NE(outPort, nullptr);
    ASSERT_NE(inPort, outPort);
    ASSERT_EQ(inPort->data, outPort->data);
  }
}

TEST(Node, PortsMismatched) {
  Node::Config cfg;
  // make some mismatched ports
  const size_t numPorts = 10;
  std::vector<std::unique_ptr<float[]>> buffers;
  for (auto i = 0; i < numPorts; ++i) {
    const size_t numSamples = i * 2 + 64;
    const size_t numChannels = i + 1;
    buffers.push_back(std::make_unique<float[]>(numSamples * numChannels));
    cfg.inputPorts.push_back({buffers[i].get(), numSamples, numChannels});
    cfg.outputPorts.push_back({nullptr, numChannels, numSamples});
  }
  // make the node
  Node node(cfg);

  // process and expect failure
  ASSERT_NE(node.process(), Status::Ok);
}

TEST(Node, PortCustomProcess) {
  Node::Config cfg;

  // make a splitter node
  const size_t numSamples = 512;
  const size_t numChannels = 2;
  std::vector<std::unique_ptr<float[]>> outBuffers;
  outBuffers.push_back(std::make_unique<float[]>(numSamples * numChannels));
  outBuffers.push_back(std::make_unique<float[]>(numSamples * numChannels));
  cfg.inputPorts.push_back({nullptr, numSamples, numChannels});
  cfg.outputPorts.push_back({outBuffers[0].get(), numSamples, numChannels});
  cfg.outputPorts.push_back({outBuffers[1].get(), numSamples, numChannels});
  cfg.processFn = [](Node &node) {
    // get the ports
    Port *in{nullptr};
    if (node.getPort(0, Node::PortType::Input, in) != Status::Ok) {
      return Status::NotFound;
    }
    if (in == nullptr) {
      return Status::Fail;
    }
    Port *out1{nullptr};
    if (node.getPort(0, Node::PortType::Output, out1) != Status::Ok) {
      return Status::NotFound;
    }
    if (out1 == nullptr) {
      return Status::Fail;
    }
    Port *out2{nullptr};
    if (node.getPort(1, Node::PortType::Output, out2) != Status::Ok) {
      return Status::NotFound;
    }
    if (out2 == nullptr) {
      return Status::Fail;
    }
    // copy the input buffer to the output buffers
    if (in->data == nullptr) {
      return Status::Uninitialized;
    }
    if (in->numSamples != out1->numSamples
        || in->numSamples != out2->numSamples
        || in->numChannels != out1->numChannels
        || in->numChannels != out2->numChannels) {
      return Status::Mismatch;
    }
    memcpy(out1->data, in->data, in->numChannels * in->numSamples * sizeof(float));
    memcpy(out2->data, in->data, in->numChannels * in->numSamples * sizeof(float));
    return Status::Ok;
  };
  Node node(cfg);

  // assign the input buffer to the input port, then process.
  const auto inBuffer = std::make_unique<float[]>(numSamples * numChannels);
  for (auto i = 0; i < numSamples * numChannels; ++i) {
    inBuffer[i] = 1.0f;
  }
  Port* in{nullptr};
  ASSERT_EQ(node.getPort(0, Node::PortType::Input, in), Status::Ok);
  ASSERT_NE(in, nullptr);
  in->data = inBuffer.get();
  ASSERT_EQ(node.process(), Status::Ok);

  // make sure the output buffers match the input buffer
  Port* out1{nullptr};
  ASSERT_EQ(node.getPort(0, Node::PortType::Output, out1), Status::Ok);
  ASSERT_NE(out1, nullptr);
  Port* out2{nullptr};
  ASSERT_EQ(node.getPort(1, Node::PortType::Output, out2), Status::Ok);
  ASSERT_NE(out2, nullptr);
  ASSERT_NE(out1, out2);
  ASSERT_NE(out1->data, out2->data);
  for (auto i = 0; i < numSamples * numChannels; ++i) {
    ASSERT_EQ(in->data[i], out1->data[i]);
    ASSERT_EQ(in->data[i], out2->data[i]);
  }
}
