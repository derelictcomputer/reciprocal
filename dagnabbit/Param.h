#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>

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
  void set(ParamType value) {
    // clamp
    value = std::clamp(value, min, max);
    // snap
    if (step > ParamType(0)) {
      const ParamType delta = value - min;
      value = min + step * std::floor(delta / step + ParamType(0.5));
    }
    // assign
    _val.store(value);
  }

  /// Get the value.
  /// @param value Will be set to the current value after return.
  /// @returns Status::Ok or appropriate error.
  ParamType get() const {
    return _val.load();
  }

  const ParamType min;
  const ParamType max;
  const ParamType def;
  const ParamType step;

private:
  std::atomic<ParamType> _val;
};

/// Just here to make toggle parameters easier to wield
class BoolParam : public Param<bool> {
public:
  explicit BoolParam(bool def) : Param<bool>(false, true, def, true) {}
};
}
