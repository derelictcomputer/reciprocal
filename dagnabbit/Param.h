#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>

namespace dc {
/// Atomic configuration value for a thing that needs configuring.
template<class T>
class Param {
public:
  explicit Param(T min, T max, T def, T step) :
      min(std::min(min, max)),
      max(std::max(min, max)),
      def(std::clamp(def, min, max)),
      step(step),
      _val(def) {
  }

  /// Set the value.
  /// @param value The value to set. Will clamp and snap based on min, max, and step.
  void set(T value) {
    // clamp
    value = std::clamp(value, min, max);
    // snap
    if (step > T(0)) {
      const T delta = value - min;
      value = min + step * std::floor(delta / step + T(0.5));
    }
    // assign
    _val.store(value);
  }

  /// Set the value using a 0.0-1.0 normalized value.
  /// @param normalized A normalized value in range 0.0-1.0
  void setNormalized(double normalized) {
    set(static_cast<T>(min + normalized * (max - min)));
  }

  /// Get the value.
  /// @returns The param's value.
  [[nodiscard]] T get() const {
    return _val.load();
  }

  /// Get the value normalized to range 0.0-1.0
  /// @returns The normalized value
  [[nodiscard]] double getNormalized() const {
    return static_cast<double>(_val.load() - min) / (max - min);
  }

  const T min;
  const T max;
  const T def;
  const T step;

private:
  std::atomic<T> _val;
};

/// Just here to make toggle parameters easier to wield
class BoolParam : public Param<bool> {
public:
  explicit BoolParam(bool def) : Param<bool>(false, true, def, true) {}
};
}
