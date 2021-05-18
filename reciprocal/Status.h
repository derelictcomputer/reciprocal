#pragma once
#include <cstdint>

namespace dc {
enum class Status : uint8_t {
  Ok = 0,
  Fail,
  SIZE
};
}
