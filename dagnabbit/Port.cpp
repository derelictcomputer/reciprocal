#include "Port.h"

using namespace dc;

IPort::IPort(const IPort::Config& cfg) :
typeId(cfg.typeId),
prettyName(cfg.prettyName),
maxConnections(cfg.maxConnections),
_connections(new std::atomic<IPort*>[maxConnections]) {
  for (size_t i = 0; i < maxConnections; ++i) {
    _connections[i] = nullptr;
  }
}

size_t IPort::getNumConnections() const {
  size_t count{0};
  for (size_t i = 0; i < maxConnections; ++i) {
    if (_connections[i] != nullptr) {
      ++count;
    }
  }
  return count;
}

bool IPort::isConnectedTo(IPort* other) {
  if (other == nullptr) {
    return false;
  }

  for (size_t i = 0; i < maxConnections; ++i) {
    if (_connections[i] == other) {
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

  for (size_t i = 0; i < maxConnections; ++i) {
    auto current = _connections[i].load();
    if (current == nullptr && _connections[i].compare_exchange_strong(current, other)) {
      const auto status = other->connect(this);
      // Something went wrong, disconnect.
      if (status != Status::Ok) {
        _connections[i] = nullptr;
      }
      return status;
    }
  }

  return Status::Full;
}

Status IPort::disconnect(IPort* other) {
  for (size_t i = 0; i < maxConnections; ++i) {
    auto current = _connections[i].load();
    if (current == other && _connections[i].compare_exchange_strong(current, nullptr)) {
      for (size_t j = 0; j < other->maxConnections; ++j) {
        current = other->_connections[j].load();
        if (current == this) {
          return other->_connections[j].compare_exchange_strong(current, nullptr) ? Status::Ok : Status::Fail;
        }
      }
    }
  }

  return Status::NotFound;
}

Status IPort::disconnectAll() {
  for (size_t i = 0; i < maxConnections; ++i) {
    auto& c = _connections[i];
    auto other = c.load();
    c = nullptr;
    if (other != nullptr) {
      for (size_t j = 0; j < other->maxConnections; ++j) {
        auto& oc = other->_connections[j];
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
