#pragma once

#include <algorithm>
#include <atomic>
#include <cmath>
#include <string>

namespace dc {
class ParamBase {
public:
  explicit ParamBase(std::string&& name) : name(std::move(name)) {}

  const std::string name;

  /// Set the value using a 0.0-1.0 normalized value.
  /// @param normalized A normalized value in range 0.0-1.0
  virtual void setNormalized(double normalized) = 0;

  /// Get the value normalized to range 0.0-1.0
  /// @returns The normalized value
  [[nodiscard]] virtual double getNormalized() const = 0;
};

/// Atomic configuration value for a thing that needs configuring.
template<class T>
class Param : public ParamBase {
public:
  explicit Param(std::string&& name, T min, T max, T def, T step) :
      ParamBase(std::move(name)),
      min(std::min(min, max)),
      max(std::max(min, max)),
      def(std::clamp(def, min, max)),
      step(step),
      _val(def) {
  }

  Param(const Param& other) noexcept:
      ParamBase(std::string(other.name)),
      min(other.min),
      max(other.max),
      def(other.def),
      step(other.step),
      _val(other._val.load()) {
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
  void setNormalized(double normalized) override {
    set(static_cast<T>(min + normalized * (max - min)));
  }

  /// Get the value.
  /// @returns The param's value.
  [[nodiscard]] T get() const {
    return _val.load();
  }

  /// Get the value normalized to range 0.0-1.0
  /// @returns The normalized value
  [[nodiscard]] double getNormalized() const override {
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
  explicit BoolParam(std::string&& name, bool def) : Param<bool>(std::move(name), false, true, def, false) {}
};
}
