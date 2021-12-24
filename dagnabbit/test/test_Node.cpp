#include <gtest/gtest.h>
#include "../Node.h"

using namespace dc;

TEST(Node, Constraint) {
  Node<Message<float, 4, int>> node;
  auto msg = node.makeMessage();
  ASSERT_EQ(msg.dataSize, 4);
}
