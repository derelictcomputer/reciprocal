#include <cassert>
#include <utility>
#include "Port.h"

using namespace dc;

IPort::IPort(std::string  prettyName, size_t maxConnections, size_t typeId, size_t canConnectToTypeId) :
typeId(typeId),
canConnectToTypeId(canConnectToTypeId),
prettyName(std::move(prettyName)),
maxConnections(maxConnections) {
  _connections.reserve(maxConnections);
}

IPort::~IPort() {} // NOLINT(modernize-use-equals-default)

size_t IPort::getNumConnections() const {
  return _connections.size();
}

bool IPort::isConnectedTo(IPort* other) {
  if (other == nullptr) {
    return false;
  }

  for (auto c: _connections) {
    if (c == other) {
      return true;
    }
  }

  return false;
}

Status IPort::connect(IPort* other) {
  if (canConnectToTypeId != other->typeId) {
    return Status::TypeMismatch;
  }

  // Too many connections.
  if (getNumConnections() >= maxConnections || other->getNumConnections() >= other->maxConnections) {
    return Status::Full;
  }

  // Already connected. Pretend it succeeded.
  if (isConnectedTo(other)) {
    assert(other->isConnectedTo(this));
    return Status::Ok;
  }

  _connections.push_back(other);
  other->_connections.push_back(this);
  return Status::Ok;
}

Status IPort::disconnect(IPort* other) {
  for (auto it = _connections.begin(); it != _connections.end(); ++it) {
    if (*it == other) {
      _connections.erase(it);

      for (it = other->_connections.begin(); it != other->_connections.end(); ++it) {
        if (*it == this) {
          other->_connections.erase(it);
          return Status::Ok;
        }
      }

      // If we get here, there was asymmetry in connections. Bad news.
      return Status::Fail;
    }
  }

  return Status::NotFound;
}

Status IPort::disconnectAll() {
  for (auto c : _connections) {
    assert(c != nullptr);
    bool foundMe = false;

    for (auto it = c->_connections.begin(); it != c->_connections.end(); ++it) {
      if (*it == this) {
        c->_connections.erase(it);
        foundMe = true;
        break;
      }
    }

    // The other port did not have this one in their connection list. Bad news.
    if (!foundMe) {
      return Status::Fail;
    }
  }

  _connections.clear();

  return Status::Ok;
}
