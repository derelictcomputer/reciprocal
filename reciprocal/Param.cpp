#include "Param.h"
#include <algorithm>
#include <cmath>

dc::Param::Param(float min, float max, float def, float step) : min(min), max(max), def(def), step(step) {
  _val = def;
}

dc::Status dc::Param::set(float value) {
  _val = snap(clamp(value, min, max), step);
  return dc::Status::Ok;
}

dc::Status dc::Param::get(float &value) {
  value = _val;
  return dc::Status::Ok;
}

float dc::Param::snap(float value, float step) {
  if (step > 0.0f)
  {
    return step * std::floor(value / step + 0.5f);
  }
  return value;
}

float dc::Param::clamp(float value, float min, float max) {
  if (max > min)
  {
    return std::min(max, std::max(min, value));
  }
  return std::max(max, std::min(min, value));
}
