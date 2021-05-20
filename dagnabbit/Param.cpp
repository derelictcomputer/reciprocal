#include "Param.h"
#include <algorithm>
#include <cmath>

dc::Param::Param(float min, float max, float def, float step) : min(min), max(max), def(def), step(step) {
  _val = def;
}

dc::Status dc::Param::set(float value) {
  // clamp
  _val = max > min ? std::min(max, std::max(min, value)) : std::max(max, std::min(min, value));
  // snap
  const float delta = _val - min;
  _val = min + step * std::floor(delta / step + 0.5f);
  return dc::Status::Ok;
}

dc::Status dc::Param::get(float &value) const {
  value = _val;
  return dc::Status::Ok;
}
