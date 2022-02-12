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

const double rateMin = 1.0 / 8.0; // 1/8th of a 1/4 note is a 32nd note
const double rateMax = 4.0; // whole note (4 * 1/4 note)
const double rateDef = 1.0 / 4.0; // 1/4th of a 1/4 note is a 16th note
const double rateStep = 1.0 / 8.0;
const uint8_t stepsDef = 16;
const uint8_t pulsesDef = 4;
const uint8_t stepsMin = 1;
const uint8_t stepsMax = 16;
}
