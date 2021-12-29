#pragma once

#include "Port.h"

namespace dc {
template<class TimeType>
class Node {
public:
  virtual Status process(TimeType now, TimeType deltaTime) = 0;
};
}
