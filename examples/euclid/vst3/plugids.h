#pragma once

namespace dc::euclid {
static const Steinberg::FUID EuclidProcId (0x16f43722, 0xc2ce4bd2, 0xba08d59f, 0xc7232e29);
static const Steinberg::FUID EuclidControllerId (0x9b79ee27, 0xeba44c06, 0xb777666d, 0xde7690bd);

enum class ParamId {
  Enable,
  Rate,
  Pulses,
  Steps,
  COUNT
};

constexpr double rateMin = 1.0 / 8.0; // 1/8th of a 1/4 note is a 32nd note
constexpr double rateMax = 4.0; // whole note (4 * 1/4 note)
constexpr double rateDef = 1.0 / 4.0; // 1/4th of a 1/4 note is a 16th note
constexpr double rateStep = 1.0 / 8.0;
constexpr uint8_t stepsDef = 16;
constexpr uint8_t pulsesDef = 4;
constexpr uint8_t stepsMin = 1;
constexpr uint8_t stepsMax = 16;
}
