#ifndef SIM_CHARACTER_H_
#define SIM_CHARACTER_H_

#include "sim/game-interface.h"
#include "util/coordinate.h"

// Includes utilities
class Character {
 public:
  Character() {}
  virtual ~Character() {}

  // Accessors
  Coordinate GetRC() const { return Coordinate(r_, c_); }
  Coordinate GetInitialRC() const { return Coordinate(initial_r_, initial_c_); }
  int GetDirection() const { return d_; }

  // Following are for internal use
  void SetRC(int r, int c) {
    r_ = r;
    c_ = c;
  }
  void SetDirection(int d) { d_ = d; }
  void Initialize(int r, int c, int d) {
    initial_r_ = r;
    initial_c_ = c;
    initial_d_ = d;
    ResetPositionAndDirection();
  }
  void ResetPositionAndDirection() {
    r_ = initial_r_;
    c_ = initial_c_;
    d_ = initial_d_;
  }
  bool CanMove(const GameInterface& game, int d) const;
  bool Move();

 protected:
  int r_;
  int c_;
  int d_;  // direction
  int initial_r_;
  int initial_c_;
  int initial_d_;
};

#endif  // SIM_CHARACTER_H_
