#include "Param.h"
#include <algorithm>
#include <cmath>

dc::Param::Param(Config cfg) : min(cfg.min), max(cfg.max), def(cfg.def), step(cfg.step) {
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
