#pragma once

#include "Status.h"

namespace dc {
class Param {
public:
  struct Config {
    float min{0};
    float max{0};
    float def{0};
    float step{0};
  };

  explicit Param(Config cfg);

  Status set(float value);
  Status get(float& value) const;

  const float min;
  const float max;
  const float def;
  const float step;

private:
  float _val;
};
}
