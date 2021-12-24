#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>
#include "../core/Status.h"

namespace dc {
/// Atomic configuration value for a thing that needs configuring.
template<class ParamType>
class Param {
public:
  explicit Param(ParamType min, ParamType max, ParamType def, ParamType step) :
      min(std::min(min, max)),
      max(std::max(min, max)),
      def(std::clamp(def, min, max)),
      step(step),
      _val(def) {
  }

  /// Set the value.
  /// @param value The value to set. Will clamp and snap based on min, max, and step.
  /// @returns Status::Ok or appropriate error.
  Status set(ParamType value) {
    // clamp
    value = std::clamp(value, min, max);
    // snap
    if (step > ParamType(0)) {
      const ParamType delta = value - min;
      value = min + step * std::floor(delta / step + ParamType(0.5));
    }
    // assign
    _val = value;
    return Status::Ok;
  }

  /// Get the value.
  /// @param value Will be set to the current value after return.
  /// @returns Status::Ok or appropriate error.
  Status get(ParamType& value) const {
    value = _val;
    return Status::Ok;
  }

  const ParamType min;
  const ParamType max;
  const ParamType def;
  const ParamType step;

private:
  std::atomic<ParamType> _val;
};
}
