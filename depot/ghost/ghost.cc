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

void Ghost::INT3() {
  register_a_ = GetGhostIndex();
}

void Ghost::INT4() {
  Ghost::ReturnCoordinate(game_->GetGhostInitialRC(register_a_));
}

void Ghost::INT5() {
  Ghost::ReturnCoordinate(game_->GetGhostRC(register_a_));
}

void Ghost::INT6() {
  int ghost_index = register_a_;
  int vitality = game_->GetGhostVitality(ghost_index);
  int direction = game_->GetGhostDirection(ghost_index);
  if (vitality == -1 || direction == -1) {
    error_ = true;
    return;
  }
  register_a_ = vitality;
  register_b_ = direction;
}

void Ghost::INT7() {
  char symbol = game_->GetSymbol(Coordinate(register_b_, register_a_));
  switch (symbol) {
    // 0: Wall (#)
    case '#': register_a_ = 0; break;
    // 1: Empty (<space>)
    case ' ': register_a_ = 1; break;
    // 2: Pill
    case '.': register_a_ = 2; break;
    // 3: Power pill
    case 'O': register_a_ = 3; break;
    // 4: Fruit
    case '%': register_a_ = 4; break;
    // 5: Lambda-Man starting position
    case '\\': register_a_ = 5; break;
    // 6: Ghost starting position
    case '=': register_a_ = 6; break;
    // Accessed out of area.
    case '?': error_ = true; break;
    default:
      LOG(ERROR) << "unknown map symbol: " << symbol;
  }
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
