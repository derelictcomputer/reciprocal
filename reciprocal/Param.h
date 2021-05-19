#pragma once

#include "Status.h"

namespace dc {
class Param {
public:
  Param(float min, float max, float def, float step);

  static float snap(float value, float step);
  static float clamp(float value, float min, float max);

  Status set(float value);
  Status get(float& value);

  const float min;
  const float max;
  const float def;
  const float step;

private:
  float _val;
};
}
