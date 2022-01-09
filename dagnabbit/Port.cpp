#include <cassert>
#include "Port.h"

using namespace dc;

IPort::IPort(const IPort::Config& cfg) :
typeId(cfg.typeId),
prettyName(cfg.prettyName),
maxConnections(cfg.maxConnections),
_connections(cfg.maxConnections) {
  assert(_connections.size() == maxConnections);
  for (auto& c : _connections) {
    c = nullptr;
  }
}

size_t IPort::getNumConnections() const {
  size_t count{0};
  for (const auto& c : _connections) {
    if (c != nullptr) {
      ++count;
    }
  }
  return count;
}

bool IPort::isConnectedTo(IPort* other) {
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

Status IPort::connect(IPort* other) {
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

Status IPort::disconnect(IPort* other) {
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

Status IPort::disconnectAll() {
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
