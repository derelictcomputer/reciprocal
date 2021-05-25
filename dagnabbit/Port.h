#pragma once

namespace dc {
struct Port {
  float* data{nullptr};
  size_t numSamples{0};
  size_t numChannels{0};
};
}
