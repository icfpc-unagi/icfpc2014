#include "util/coordinate.h"

// static
Coordinate CoordinateUtil::Null() {
  return Coordinate(-1, -1);
}

// static
bool CoordinateUtil::IsNull(const Coordinate& coordinate) {
  return coordinate == Null();
}
