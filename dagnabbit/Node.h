#pragma once

#include <concepts>
#include "Message.h"
#include "../core/Status.h"

namespace dc {
template<MessageSpecialization MessageType>
class Node {
public:
  MessageType makeMessage() {
    MessageType msg;
    return msg;
  }
};
}
