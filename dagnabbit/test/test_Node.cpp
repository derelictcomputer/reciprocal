#include <gtest/gtest.h>
#include <memory>
#include "../Node.h"

using namespace dc;

TEST(Node, Proc) {
  size_t numProcessCalls{0};
  bool userDataValue = true;
  Node::Config cfg;
  cfg.userData = &userDataValue;
  cfg.processFn = [&numProcessCalls](Node::ProcessCtx ctx) -> Status {
    ++numProcessCalls;
    if (ctx.userData == nullptr){
      return Status::Fail;
    }
    bool udv = *static_cast<bool*>(ctx.userData);
    return udv ? Status::Ok : Status::Fail;
  };
  Node node(cfg);
  ASSERT_EQ(node.process(), Status::Ok);
  ASSERT_EQ(numProcessCalls, 1);
}

TEST(Node, Params) {
  const uint16_t numParams = 5;
  Node::Config cfg;
  for (uint16_t i = 0; i < numParams; ++i) {
    const float min = i;
    const float max = i + 10.0f;
    const float def = (max - min) / 2.0f;
    const float step = 10.0f / (i + 1);
    cfg.params.emplace_back(min, max, def, step);
  }

  Node node(cfg);
  ASSERT_EQ(node.numParams(), numParams);
}
