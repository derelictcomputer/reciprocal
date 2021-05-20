#pragma once

#include "Status.h"

namespace dc {
class Param {
public:
  Param(float min, float max, float def, float step);

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
