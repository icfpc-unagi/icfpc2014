#ifndef SIM_GAME_INTERFACE_H_
#define SIM_GAME_INTERFACE_H_

#include "util/coordinate.h"

class GameInterface {
 public:
  //////////////////////////////////////////////////////////////////////////////
  // APIs for Ghost
  //////////////////////////////////////////////////////////////////////////////
  virtual Coordinate GetFirstLambdaManRC() const = 0;
  virtual Coordinate GetSecondLambdaManRC() const = 0;
  virtual Coordinate GetGhostInitialRC(int ghost_index) const = 0;
  virtual Coordinate GetGhostRC(int ghost_index) const = 0;
  virtual int GetGhostVitality(int ghost_index) const = 0;
  virtual int GetGhostDirection(int ghost_index) const = 0;
};

#endif  // SIM_GAME_INTERFACE_H_
