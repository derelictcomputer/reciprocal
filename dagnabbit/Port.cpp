#include <cassert>
#include "Port.h"

using namespace dc;

Port::Port(const Port::Config& cfg) :
typeId(cfg.typeId),
prettyName(cfg.prettyName),
maxConnections(cfg.maxConnections),
_connections(cfg.maxConnections),
_destroyMessageQueueFn(cfg.destroyMessageQueueFn) {
  if (cfg.createMessageQueueFn != nullptr) {
    assert(cfg.destroyMessageQueueFn != nullptr);
    _messageQueue = cfg.createMessageQueueFn();
  }
}

size_t Port::getNumConnections() const {
  return _connections.size();
}

bool Port::isConnectedTo(Port* other) {
  return _connections.find(
      [other](Port* const& p) {
        return p == other;
      },
      [](Port*&) {}) == Status::Ok;
}

Status Port::connect(Port* other) {
  if (other->typeId != typeId) {
    return Status::TypeMismatch;
  }

  auto status = other->_connections.add([this](Port*& p) {
    p = this;
  });
  if (status != Status::Ok) {
    return status;
  }

  status = _connections.add([other](Port*& p) {
    p = other;
  });
  if (status != Status::Ok) {
    [[maybe_unused]] const auto s = other->_connections.remove(
        [this](Port* const& p) {
          return p == this;
        },
        [](Port*& p) {
          p = nullptr;
        });
    assert(s == Status::Ok);
    return status;
  }

  return Status::Ok;
}

Status Port::disconnect(Port* other) {
  auto status = _connections.remove(
      [other](Port* const& p) {
        return p == other;
      },
      [](Port*& p) {
        p = nullptr;
      });
  if (status != Status::Ok) {
    return status;
  }

  return other->_connections.remove(
      [this](Port* const& p) {
        return p == this;
      },
      [](Port*& p) {
        p = nullptr;
      });
}

Status Port::disconnectAll() {
  return _connections.clear([this](Port*& other) {
    [[maybe_unused]] const auto status = other->_connections.remove(
        [this](Port* const& p) {
          return p == this;
        },
        [](Port*& p) {
          p = nullptr;
        });
    assert(status == Status::Ok);
    other = nullptr;
  });
}

Status Port::getMessageQueue(void*& messageQueue) {
  if (_messageQueue == nullptr) {
    return Status::NotFound;
  }
  messageQueue = _messageQueue;
  return Status::Ok;
}
