#include <gtest/gtest.h>
#include <memory>
#include "../Node.h"

using namespace dc;

TEST(Node, Create) {
  auto node = std::make_unique<Node>(Node::Config());
  ASSERT_NE(node, nullptr);
}

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
  auto node = std::make_unique<Node>(cfg);
  ASSERT_EQ(node->process(), Status::Ok);
  ASSERT_EQ(numProcessCalls, 1);
}
