#pragma once

#include <functional>
#include <unordered_map>
#include "../third_party/rigtorp/MPMCQueue.h"
#include "Node.h"

namespace dc {
using NodeId = size_t;
NodeId InvalidNodeId = 0;

template<class TimeType>
class Graph {
public:
  using NodeType = Node<TimeType>;

  explicit Graph(size_t asyncQueueSize, size_t capacity) : capacity(capacity), _asyncQ(asyncQueueSize) {
    _nodes.reserve(capacity);
    _availableNodeIds.reserve(capacity);
    for (size_t i = 0; i < capacity; ++i) {
      _availableNodeIds.push_back(i + 1);
    }
  }

  const size_t capacity;

  size_t size() const {
    return _size;
  }

  using AddNodeCb = std::function<void(Status, NodeId)>;

  Status addNode(NodeType* node, AddNodeCb&& addNodeCb) {
    const auto async = [this, node, &addNodeCb]() {
      if (_nodes.size() >= capacity) {
        addNodeCb(Status::Full, InvalidNodeId);
        return;
      }

      const auto nodeId = getAvailableNodeId();
      if (nodeId == InvalidNodeId) {
        addNodeCb(Status::Fail, InvalidNodeId);
        return;
      }

      const auto success = _nodes.emplace(nodeId, node).second;

      if (success) {
        ++_size;
        addNodeCb(Status::Ok, nodeId);
      }
      else {
        addNodeCb(Status::Fail, InvalidNodeId);
      }
    };
    return _asyncQ.try_push<std::function<void()>>(std::move(async)) ? Status::Ok : Status::Full;
  }

  Status process() {
    // perform the async operations
    {
      std::function<void()> asyncFn;
      while (_asyncQ.try_pop(asyncFn)) {
        asyncFn();
      }
    }

    // TODO: process the nodes

    return Status::Ok;
  }

private:
  rigtorp::MPMCQueue<std::function<void()>> _asyncQ;
  std::unordered_map<NodeId, std::unique_ptr<NodeType>> _nodes;
  std::atomic<size_t> _size{0};

  // quick and dirty locally unique id, only to be used from the process thread
  std::vector<NodeId> _availableNodeIds;

  NodeId getAvailableNodeId() {
    if (_availableNodeIds.empty()) {
      return InvalidNodeId;
    }
    const auto endId = _availableNodeIds[_availableNodeIds.size() - 1];
    _availableNodeIds.pop_back();
    return endId;
  }
};
}
