#include "sim/character.h"

#include "sim/game-interface.h"
#include "util/coordinate.h"

namespace {
constexpr int dr[4] = {-1, 0, 1, 0};
constexpr int dc[4] = {0, 1, 0, -1};
}  // namespace

bool Character::CanMove(const GameInterface& game, int d) const {
  return game.GetSymbolSafe(Coordinate(r_ + dr[d], c_ + dc[d]), '#') != '#';
}

bool Character::Move() {
  switch (d_) {
    case 0:
      r_--;
      return true;
    case 1:
      c_++;
      return true;
    case 2:
      r_++;
      return true;
    case 3:
      c_--;
      return true;
  }
  return false;
}
