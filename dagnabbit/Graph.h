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
    // Custom deleter, so whenever the shared pointer's ref count goes to zero,
    // the TrashMan thread takes care of deleting instead of possibly the process thread.
    const auto deleter = [this](NodeType* ptr) {
      if (ptr != nullptr) {
        [[maybe_unused]] const auto status = _trashMan.trash(ptr);
        assert(status == Status::Ok && ptr == nullptr);
      }
    };
    // Make a shared pointer here, so if enqueuing the add request fails, the node gets cleaned up.
    std::shared_ptr<NodeType> node(createNodeFn(), deleter);
    assert(node != nullptr);

    // When we capture the shared pointer by value here, it creates a copy and increases the ref count.
    const auto async = [this, node, addNodeCb]() {
      if (_nodes.size() >= capacity) {
        addNodeCb(Status::Full, InvalidNodeId);
        return;
      }

      // get a node id for the new node
      const auto nodeId = getAvailableNodeId();
      if (nodeId == InvalidNodeId) {
        addNodeCb(Status::Fail, InvalidNodeId);
        return;
      }

      // When we move/emplace here it should avoid another copy
      const auto success = _nodes.emplace(nodeId, std::move(node)).second;

      if (success) {
        // we store the size separately so it can be accessed from any thread
        // it'll only update once process is called
        _size = _nodes.size();
        addNodeCb(Status::Ok, nodeId);
      }
      else {
        returnNodeId(nodeId);
        addNodeCb(Status::Fail, InvalidNodeId);
      }
    };

    return _asyncQ.try_push<std::function<void()>>(std::move(async)) ? Status::Ok : Status::Full;
  }

  using RemoveNodeCb = std::function<void(Status, NodeId)>;

  /// Request to remove a node from the graph
  /// @param nodeId The id of the node to remove
  /// @param removeNodeCb A callback to let you know if the removal was successful.
  /// @returns Status::Ok if the request was enqueued, Status::Full if the async queue was full.
  Status removeNode(NodeId nodeId, const RemoveNodeCb& removeNodeCb) {
    const auto async = [this, nodeId, removeNodeCb]() {
      // NB: we can just call erase here because we store a shared pointer
      // with a deleter that offloads the actual deletion of the node to a cleanup thread.
      const auto erased = _nodes.erase(nodeId);
      _size = _nodes.size();
      removeNodeCb(erased == 1 ? Status::Ok : Status::NotFound, nodeId);
    };

    return _asyncQ.try_push<std::function<void()>>(std::move(async)) ? Status::Ok : Status::Full;
  }

  /// Update the graph's state and process its nodes
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

  void returnNodeId(NodeId id) {
    if (id == InvalidNodeId || _availableNodeIds.size() == _availableNodeIds.capacity()) {
      return;
    }
    _availableNodeIds.push_back(id);
  }
};
}
