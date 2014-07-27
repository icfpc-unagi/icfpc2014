#ifndef GHOST_AI_FICKLE_DEBUG_H_
#define GHOST_AI_FICKLE_DEBUG_H_

#include "ghost/ghost.h"

#include <glog/logging.h>

namespace ghost {

class fickle_debugGhost : public Ghost {
  void Run() override {
    ResetTick();
pc000: if (Tick()) return;
    register_pc_ = 0;
    VLOG(3) << "[0] mov a,255";
    MOV(register_a_, 255);
pc001: if (Tick()) return;
    register_pc_ = 1;
    VLOG(3) << "[1] mov b,0";
    MOV(register_b_, 0);
pc002: if (Tick()) return;
    register_pc_ = 2;
    VLOG(3) << "[2] mov c,255";
    MOV(register_c_, 255);
pc003: if (Tick()) return;
    register_pc_ = 3;
    VLOG(3) << "[3] inc c";
    INC(register_c_);
pc004: if (Tick()) return;
    register_pc_ = 4;
    VLOG(3) << "[4] jgt 7,[c],a";
    if (JGT(Memory(register_c_), register_a_)) goto pc007;
pc005: if (Tick()) return;
    register_pc_ = 5;
    VLOG(3) << "[5] mov a,[c]";
    MOV(register_a_, Memory(register_c_));
pc006: if (Tick()) return;
    register_pc_ = 6;
    VLOG(3) << "[6] mov b,c";
    MOV(register_b_, register_c_);
pc007: if (Tick()) return;
    register_pc_ = 7;
    VLOG(3) << "[7] jlt 3,c,3";
    if (JLT(register_c_, 3)) goto pc003;
pc008: if (Tick()) return;
    register_pc_ = 8;
    VLOG(3) << "[8] mov a,b";
    MOV(register_a_, register_b_);
pc009: if (Tick()) return;
    register_pc_ = 9;
    VLOG(3) << "[9] int 0";
    INT0();
pc010: if (Tick()) return;
    register_pc_ = 10;
    VLOG(3) << "[10] int 8";
    INT8();
pc011: if (Tick()) return;
    register_pc_ = 11;
    VLOG(3) << "[11] int 3";
    INT3();
pc012: if (Tick()) return;
    register_pc_ = 12;
    VLOG(3) << "[12] int 6";
    INT6();
pc013: if (Tick()) return;
    register_pc_ = 13;
    VLOG(3) << "[13] inc [b]";
    INC(Memory(register_b_));
pc014: if (Tick()) return;
    register_pc_ = 14;
    VLOG(3) << "[14] hlt";
    HLT();
  }
};

class fickle_debugGhostFactory : public ::GhostFactory {
 public:
  virtual ~fickle_debugGhostFactory() {}

  std::unique_ptr<::GhostInterface> Create() {
    return std::unique_ptr<::GhostInterface>(new fickle_debugGhost());
  }
};

}  // namespace ghost

#endif  // GHOST_AI_FICKLE_DEBUG_H_
