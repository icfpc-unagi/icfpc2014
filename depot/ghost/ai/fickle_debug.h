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
    VLOG(3) << "[0] MOV a,255";
    MOV(register_a_, 255);
pc001: if (Tick()) return;
    register_pc_ = 1;
    VLOG(3) << "[1] INT 8";
    INT8();
pc002: if (Tick()) return;
    register_pc_ = 2;
    VLOG(3) << "[2] MOV b,0";
    MOV(register_b_, 0);
pc003: if (Tick()) return;
    register_pc_ = 3;
    VLOG(3) << "[3] INT 8";
    INT8();
pc004: if (Tick()) return;
    register_pc_ = 4;
    VLOG(3) << "[4] MOV c,255";
    MOV(register_c_, 255);
pc005: if (Tick()) return;
    register_pc_ = 5;
    VLOG(3) << "[5] INT 8";
    INT8();
pc006: if (Tick()) return;
    register_pc_ = 6;
    VLOG(3) << "[6] INC c";
    INC(register_c_);
pc007: if (Tick()) return;
    register_pc_ = 7;
    VLOG(3) << "[7] INT 8";
    INT8();
pc008: if (Tick()) return;
    register_pc_ = 8;
    VLOG(3) << "[8] JGT 16,[c],a";
    if (JGT(Memory(register_c_), register_a_)) goto pc016;
pc009: if (Tick()) return;
    register_pc_ = 9;
    VLOG(3) << "[9] INT 8";
    INT8();
pc010: if (Tick()) return;
    register_pc_ = 10;
    VLOG(3) << "[10] MOV a,[c]";
    MOV(register_a_, Memory(register_c_));
pc011: if (Tick()) return;
    register_pc_ = 11;
    VLOG(3) << "[11] INT 8";
    INT8();
pc012: if (Tick()) return;
    register_pc_ = 12;
    VLOG(3) << "[12] MOV b,c";
    MOV(register_b_, register_c_);
pc013: if (Tick()) return;
    register_pc_ = 13;
    VLOG(3) << "[13] INT 8";
    INT8();
pc014: if (Tick()) return;
    register_pc_ = 14;
    VLOG(3) << "[14] JLT 6,c,3";
    if (JLT(register_c_, 3)) goto pc006;
pc015: if (Tick()) return;
    register_pc_ = 15;
    VLOG(3) << "[15] INT 8";
    INT8();
pc016: if (Tick()) return;
    register_pc_ = 16;
    VLOG(3) << "[16] MOV a,b";
    MOV(register_a_, register_b_);
pc017: if (Tick()) return;
    register_pc_ = 17;
    VLOG(3) << "[17] INT 8";
    INT8();
pc018: if (Tick()) return;
    register_pc_ = 18;
    VLOG(3) << "[18] INT 0";
    INT0();
pc019: if (Tick()) return;
    register_pc_ = 19;
    VLOG(3) << "[19] INT 8";
    INT8();
pc020: if (Tick()) return;
    register_pc_ = 20;
    VLOG(3) << "[20] INT 3";
    INT3();
pc021: if (Tick()) return;
    register_pc_ = 21;
    VLOG(3) << "[21] INT 8";
    INT8();
pc022: if (Tick()) return;
    register_pc_ = 22;
    VLOG(3) << "[22] INT 6";
    INT6();
pc023: if (Tick()) return;
    register_pc_ = 23;
    VLOG(3) << "[23] INT 8";
    INT8();
pc024: if (Tick()) return;
    register_pc_ = 24;
    VLOG(3) << "[24] INC [b]";
    INC(Memory(register_b_));
pc025: if (Tick()) return;
    register_pc_ = 25;
    VLOG(3) << "[25] INT 8";
    INT8();
pc026: if (Tick()) return;
    register_pc_ = 26;
    VLOG(3) << "[26] HLT";
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
