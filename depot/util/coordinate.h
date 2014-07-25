#ifndef UTIL_COORDINATE_H_
#define UTIL_COORDINATE_H_

typedef pair<int, int> Coordinate;

class CoordinateUtil {
 public:
  // Returns the NULL coordinate: (-1, -1).
  static Coordinate Null();
  // Returns true iff coordinate is NULL.
  static bool IsNull(const Coordinate& coordinate);
};

#endif  // UTIL_COORDINATE_H_
