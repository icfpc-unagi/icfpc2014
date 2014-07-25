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
  Coordinate coordinate = game_->GetFirstLambdaManRC();
  if (CoordinateUtil::IsNull(coordinate)) {
    error_ = true;
    return;
  }

  register_a_ = coordinate.second;
  register_b_ = coordinate.first;
}

void Ghost::INT2() {
  Coordinate coordinate = game_->GetSecondLambdaManRC();
  if (CoordinateUtil::IsNull(coordinate)) {
    error_ = true;
    return;
  }

  register_a_ = coordinate.second;
  register_b_ = coordinate.first;
}

}  // namespace ghost
