#pragma once
#include <string>

namespace dc {
// add status types here so we get the nice conversion functions
#define status_names  \
X(Ok)                 \
X(Fail)               \
X(Full)               \
X(Empty)              \
X(TypeMismatch)       \
X(NotFound)

enum class Status {
#define X(name) name,
  status_names
#undef X
  COUNT // for iterating if needed
};

inline std::string to_string(Status status) {
  switch (status) {
#define X(name) case Status::name: return #name;
    status_names
#undef X
    case Status::COUNT:
      return "COUNT";
    default:
      return "<invalid status>";
  }
}

#undef status_names
}
