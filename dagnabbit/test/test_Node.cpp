#include <gtest/gtest.h>
#include <memory>
#include "../Node.h"

using namespace dc;

TEST(Node, Proc) {
  size_t numProcessCalls{0};
  Node::Config cfg;
  cfg.processFn = [&numProcessCalls](Node& node) -> Status {
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
