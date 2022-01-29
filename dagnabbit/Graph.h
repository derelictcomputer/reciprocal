#pragma once

#include <functional>
#include <unordered_map>
#include "../core/TrashMan.h"
#include "../third_party/rigtorp/MPMCQueue.h"
#include "Node.h"

namespace dc {
/// A locally-unique id for a node in a graph.
using NodeId = size_t;
NodeId InvalidNodeId = 0;

/// A collection of nodes to be processed.
/// @tparam TimeType The type used to represent time in the graph.
template<class TimeType>
class Graph {
public:
  using NodeType = Node<TimeType>;

  explicit Graph(size_t asyncQueueSize, size_t capacity) :
  capacity(capacity),
  _asyncQ(asyncQueueSize),
  _trashMan(capacity) {
    _nodes.reserve(capacity);
    _availableNodeIds.reserve(capacity);
    for (size_t i = 0; i < capacity; ++i) {
      _availableNodeIds.push_back(i + 1);
    }
  }

  ~Graph() {
    // TODO: use Graph::clear() when there is one.
    _nodes.clear();
  }

  /// The maximum number of nodes this graph can hold.
  const size_t capacity;

  /// The number of nodes currently in the graph.
  size_t size() const {
    return _size;
  }

  /// A function that will create and configure a node prior to adding to the graph.
  using CreateNodeFn = std::function<NodeType*()>;

  /// A callback which returns the id of the node that was added, if adding it was successful.
  using AddNodeCb = std::function<void(Status, NodeId)>;

  /// Request to add a node to the graph.
  /// @param node A pointer to a node to add to the graph
  /// @param addNodeCb A callback, which will let you know the node's id if the add was successful.
  /// @returns Status::Ok if the request was enqueued, Status::Full if the async queue was full.
  Status addNode(const CreateNodeFn& createNodeFn, const AddNodeCb& addNodeCb) {
    const auto deleter = [this](NodeType* ptr) {
      if (ptr != nullptr) {
        [[maybe_unused]] const auto status = _trashMan.trash(ptr);
        assert(status == Status::Ok && ptr == nullptr);
      }
    };
    std::shared_ptr<NodeType> node(createNodeFn(), deleter);
    assert(node != nullptr);

    const auto async = [this, node, addNodeCb]() {
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
        _size = _nodes.size();
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
  std::unordered_map<NodeId, std::shared_ptr<NodeType>> _nodes;
  std::atomic<size_t> _size{0};
  TrashMan<NodeType> _trashMan;

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
