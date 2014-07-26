#include "ghost/ghost.h"

#include "sim/sim.h"
#include "util/coordinate.h"

namespace ghost {

Ghost::Ghost()
    : register_pc_(),
      register_a_(),
      register_b_(),
      register_c_(),
      register_d_(),
      register_e_(),
      register_f_(),
      register_g_(),
      register_h_(),
      memory_(256),
      direction_(-1) {}
Ghost::~Ghost() {}

void Ghost::INT1() {
  Ghost::ReturnCoordinate(game_->GetFirstLambdaManRC());
}

void Ghost::INT2() {
  Ghost::ReturnCoordinate(game_->GetSecondLambdaManRC());
}

void Ghost::INT4() {
  Ghost::ReturnCoordinate(game_->GetGhostRC(register_a_));
}

void Ghost::ReturnCoordinate(const Coordinate& coordinate) {
  if (CoordinateUtil::IsNull(coordinate)) {
    error_ = true;
    return;
  }

  register_a_ = coordinate.second;
  register_b_ = coordinate.first;
}

}  // namespace ghost
