#pragma once

#include <functional>
#include <iostream>
#include <unordered_map>
#include "../core/TrashMan.h"
#include "../third_party/rigtorp/MPMCQueue.h"
#include "Node.h"

namespace dc {
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
    _sortedNodeIds.reserve(capacity);
  }

  ~Graph() {
    // TODO: use Graph::clear() when there is one.
    _nodes.clear();
    _trashMan.dump();
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
  /// @param createNodeFn A function that will return a pointer to a configured node of the desired type.
  /// @param addNodeCb A callback, which will let you know the node's id if the add was successful.
  /// @returns Status::Ok if the request was enqueued, Status::Full if the async queue was full.
  Status addNode(const CreateNodeFn& createNodeFn, const AddNodeCb& addNodeCb) {
    if (createNodeFn == nullptr || addNodeCb == nullptr) {
      return Status::InvalidArgument;
    }

    // Custom deleter, so whenever the shared pointer's ref count goes to zero,
    // the TrashMan thread takes care of deleting instead of possibly the process thread.
    const auto deleter = [this](NodeType* ptr) {
      if (ptr != nullptr) {
        [[maybe_unused]] const auto status = _trashMan.trash(ptr);
        if (status != Status::Ok) {
          std::cerr << "disposing of a node failed with status " << to_string(status) << ", ptr " << ptr << std::endl;
          assert(false);
        }
        assert(ptr == nullptr);
      }
    };
    // Make a shared pointer here, so if enqueuing the add request fails, the node gets cleaned up.
    std::shared_ptr<NodeType> node(createNodeFn(), deleter);
    if (node == nullptr) {
      return Status::InvalidArgument;
    }

    // When we capture the shared pointer by value here, it creates a copy and increases the ref count.
    const auto async = [this, node, addNodeCb]() {
      if (_nodes.size() >= capacity) {
        addNodeCb(Status::Full, InvalidNodeId);
        return;
      }

      // get a node id for the new node
      node->_id = getAvailableNodeId();
      if (node->_id == InvalidNodeId) {
        addNodeCb(Status::Fail, InvalidNodeId);
        return;
      }

      // When we move/emplace here it should avoid another copy
      const auto success = _nodes.emplace(node->_id, std::move(node)).second;

      if (success) {
        // we store the size separately so it can be accessed from any thread
        // it'll only update once process is called
        _size = _nodes.size();
        addNodeCb(Status::Ok, node->_id);
        _topologyChanged = true;
      }
      else {
        returnNodeId(node->_id);
        addNodeCb(Status::Fail, InvalidNodeId);
      }
    };

    return pushAsync(std::move(async));
  }

  using RemoveNodeCb = std::function<void(Status, NodeId)>;

  /// Request to remove a node from the graph
  /// @param nodeId The id of the node to remove
  /// @param removeNodeCb A callback to let you know if the removal was successful.
  /// @returns Status::Ok if the request was enqueued, or appropriate error
  Status removeNode(NodeId nodeId, const RemoveNodeCb& removeNodeCb) {
    if (nodeId == InvalidNodeId) {
      return Status::InvalidArgument;
    }

    const auto async = [this, nodeId, removeNodeCb]() {
      // NB: we can just call erase here because we store a shared pointer
      // with a deleter that offloads the actual deletion of the node to a cleanup thread.
      const auto erased = _nodes.erase(nodeId);
      if (erased) {
        returnNodeId(nodeId);
        _size = _nodes.size();
        _topologyChanged = true;
      }
      removeNodeCb(erased == 1 ? Status::Ok : Status::NotFound, nodeId);
    };

    return pushAsync(std::move(async));
  }

  using ConnectNodesCb = std::function<void(Status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx)>;

  /// Request to connect two nodes in the graph
  /// @param from The NodeId of the node whose output will be connected
  /// @param fromIdx The output port index
  /// @param to The NodeId of the node whose input will be connected
  /// @param toIdx The input port index
  /// @param cb A callback to let you know if the connection was successful
  /// @returns Status::Ok if the request was enqueued, or appropriate error
  Status connectNodes(NodeId from, size_t fromIdx, NodeId to, size_t toIdx, const ConnectNodesCb& cb) {
    if (from == InvalidNodeId || to == InvalidNodeId) {
      return Status::InvalidArgument;
    }

    const auto async = [this, from, fromIdx, to, toIdx, cb]() {
      auto fromIt = _nodes.find(from);
      auto toIt = _nodes.find(to);
      if (fromIt == _nodes.end() || toIt == _nodes.end()) {
        cb(Status::NotFound, from, fromIdx, to, toIdx);
        return;
      }
      auto status = toIt->second->connectInput(*(fromIt->second), fromIdx, toIdx);
      // if connection was successful, sort the graph
      if (status == Status::Ok) {
        _topologyChanged = true;
      }
      cb(status, from, fromIdx, to, toIdx);
    };

    return pushAsync(std::move(async));
  }

  using DisconnectNodesCb = std::function<void(Status, NodeId from, size_t fromIdx, NodeId to, size_t toIdx)>;

  /// Request to disconnect two nodes in the graph
  /// @param from The NodeId of the node whose output will be disconnected
  /// @param fromIdx The output port index
  /// @param to The NodeId of the node whose input will be disconnected
  /// @param toIdx The input port index
  /// @param cb A callback to let you know if the disconnection was successful
  /// @returns Status::Ok if the request was enqueued, or appropriate error
  Status disconnectNodes(NodeId from, size_t fromIdx, NodeId to, size_t toIdx, const DisconnectNodesCb & cb) {
    if (from == InvalidNodeId || to == InvalidNodeId) {
      return Status::InvalidArgument;
    }

    const auto async = [this, from, fromIdx, to, toIdx, cb]() {
      auto fromIt = _nodes.find(from);
      auto toIt = _nodes.find(to);
      if (fromIt == _nodes.end() || toIt == _nodes.end()) {
        cb(Status::NotFound, from, fromIdx, to, toIdx);
        return;
      }
      const auto status = toIt->second->disconnectInput(*(fromIt->second), fromIdx, toIdx);
      if (status == Status::Ok) {
        _topologyChanged = true;
      }
      cb(status, from, fromIdx, to, toIdx);
    };

    return pushAsync(std::move(async));
  }

  /// Update the graph's state and process its nodes
  Status process(const TimeType& deltaTime = TimeType(0)) {
    // perform the async operations
    {
      std::function<void()> asyncFn;
      while (_asyncQ.try_pop(asyncFn)) {
        asyncFn();
      }
    }

    if (_topologyChanged) {
      sortNodes();
      _topologyChanged = false;
    }

    // nodes are sorted in reverse order
    for (auto it = _sortedNodeIds.rbegin(); it != _sortedNodeIds.rend(); ++it) {
      _nodes[*it]->process(_now, deltaTime);
    }
    _now += deltaTime;

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

  Status pushAsync(std::function<void()>&& async) {
    // dump the trash if needed
    if (_trashMan.size() > 0) {
      _trashMan.dump();
    }
    return _asyncQ.try_push<std::function<void()>>(std::move(async)) ? Status::Ok : Status::Full;
  }

  bool _topologyChanged{false};
  std::vector<NodeId> _sortedNodeIds;

  Status addBranch(NodeBase* node) {
    if (node->_visited) {
      return Status::Ok;
    }

    node->_visited = true;

    for (auto output : node->_outputs) {
      for (size_t i = 0; i < output->getNumConnections(); ++i) {
        PortBase* connection;
        auto status = output->getConnection(i, connection);
        if (status != Status::Ok) {
          return status;
        }
        if (!connection->parent->_visited) {
          addBranch(connection->parent);
        }
      }
    }

    // add the node to the list
    _sortedNodeIds.push_back(node->_id);
    return Status::Ok;
  }

  Status sortNodes() {
    _sortedNodeIds.clear();

    for (auto& [_, node] : _nodes) {
      node->_visited = false;
    }

    for (auto& [_, node] : _nodes) {
      if (!node->_visited) {
        const auto status = addBranch(node.get());
        if (status != Status::Ok) {
          return status;
        }
      }
    }

    return Status::Ok;
  }

  TimeType _now{0};
};
}
