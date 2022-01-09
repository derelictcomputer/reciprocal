#include <cassert>
#include "Port.h"

using namespace dc;

Port::Port(const Port::Config& cfg) :
typeId(cfg.typeId),
prettyName(cfg.prettyName),
maxConnections(cfg.maxConnections),
_connections(cfg.maxConnections),
_destroyMessageQueueFn(cfg.destroyMessageQueueFn) {
  assert(_connections.size() == maxConnections);
  for (auto& c : _connections) {
    c = nullptr;
  }

  if (cfg.createMessageQueueFn != nullptr) {
    assert(_destroyMessageQueueFn != nullptr);
    _messageQueue = cfg.createMessageQueueFn();
  }
}

Port::~Port() {
  if (_messageQueue != nullptr) {
    assert(_destroyMessageQueueFn != nullptr);
    _destroyMessageQueueFn(_messageQueue);
  }
}

size_t Port::getNumConnections() const {
  size_t count{0};
  for (const auto& c : _connections) {
    if (c != nullptr) {
      ++count;
    }
  }
  return count;
}

bool Port::isConnectedTo(Port* other) {
  if (other == nullptr) {
    return false;
  }

  for (auto& c : _connections) {
    if (c == other) {
      return true;
    }
  }

  return false;
}

Status Port::connect(Port* other) {
  // Wrong port type
  if (other->typeId != typeId) {
    return Status::TypeMismatch;
  }

  // Already connected. Pretend it succeeded.
  if (isConnectedTo(other)) {
    return Status::Ok;
  }

  for (auto& c : _connections) {
    auto current = c.load();
    if (current == nullptr && c.compare_exchange_strong(current, other)) {
      const auto status = other->connect(this);
      // Something went wrong, disconnect.
      if (status != Status::Ok) {
        c = nullptr;
      }
      return status;
    }
  }

  return Status::Full;
}

Status Port::disconnect(Port* other) {
  for (auto& c : _connections) {
    auto current = c.load();
    if (current == other && c.compare_exchange_strong(current, nullptr)) {
      for (auto& oc : other->_connections) {
        current = oc.load();
        if (current == this) {
          return oc.compare_exchange_strong(current, nullptr) ? Status::Ok : Status::Fail;
        }
      }
    }
  }

  return Status::NotFound;
}

Status Port::disconnectAll() {
  for (auto& c : _connections) {
    auto other = c.load();
    c = nullptr;
    if (other != nullptr) {
      for (auto& oc : other->_connections) {
        auto maybeThis = oc.load();
        if (maybeThis == this) {
          if (!oc.compare_exchange_strong(maybeThis, nullptr)) {
            return Status::Fail;
          }
        }
      }
    }
  }

  return Status::Ok;
}

Status Port::getMessageQueue(void*& messageQueue) {
  if (_messageQueue == nullptr) {
    return Status::NotFound;
  }
  messageQueue = _messageQueue;
  return Status::Ok;
}
