#include "ghost/ghost.h"

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
      memory_(256) {}
Ghost::~Ghost() {}

}  // namespace ghost
