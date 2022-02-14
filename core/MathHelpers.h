#pragma once

#include <cstddef>

namespace dc {
// from https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
template<class T>
constexpr T nextPowerOfTwo(T n) requires (std::is_integral_v<T> && std::is_unsigned_v<T>) {
  const size_t widthBytes = sizeof(T);
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  if constexpr(widthBytes > 1) {
    n |= n >> 8;
  }
  if constexpr(widthBytes > 2) {
    n |= n >> 16;
  }
  if constexpr(widthBytes > 4) {
    n |= n >> 32;
  }
  return ++n;
}
}
