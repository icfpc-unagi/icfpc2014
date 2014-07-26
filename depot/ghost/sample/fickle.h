#include "ghost/ghost.h"

#include <glog/logging.h>

namespace ghost {

class FickleGhost : public Ghost {
  void Run() override {
    ResetTick();
pc000: if (Tick()) return;
    register_pc_ = 0;
    VLOG(1) << "[0] mov a,255";
    MOV(register_a_, 255);
pc001: if (Tick()) return;
    register_pc_ = 1;
    VLOG(1) << "[1] mov b,0";
    MOV(register_b_, 0);
pc002: if (Tick()) return;
    register_pc_ = 2;
    VLOG(1) << "[2] mov c,255";
    MOV(register_c_, 255);
pc003: if (Tick()) return;
    register_pc_ = 3;
    VLOG(1) << "[3] inc c";
    INC(register_c_);
pc004: if (Tick()) return;
    register_pc_ = 4;
    VLOG(1) << "[4] jgt 7,[c],a";
    if (JGT(Memory(register_c_), register_a_)) goto pc007;
pc005: if (Tick()) return;
    register_pc_ = 5;
    VLOG(1) << "[5] mov a,[c]";
    MOV(register_a_, Memory(register_c_));
pc006: if (Tick()) return;
    register_pc_ = 6;
    VLOG(1) << "[6] mov b,c";
    MOV(register_b_, register_c_);
pc007: if (Tick()) return;
    register_pc_ = 7;
    VLOG(1) << "[7] jlt 3,c,3";
    if (JLT(register_c_, 3)) goto pc003;
pc008: if (Tick()) return;
    register_pc_ = 8;
    VLOG(1) << "[8] mov a,b";
    MOV(register_a_, register_b_);
pc009: if (Tick()) return;
    register_pc_ = 9;
    VLOG(1) << "[9] int 0";
    INT0();
pc010: if (Tick()) return;
    register_pc_ = 10;
    VLOG(1) << "[10] int 3";
    INT3();
pc011: if (Tick()) return;
    register_pc_ = 11;
    VLOG(1) << "[11] int 6";
    INT6();
pc012: if (Tick()) return;
    register_pc_ = 12;
    VLOG(1) << "[12] inc [b]";
    INC(Memory(register_b_));
pc013: if (Tick()) return;
    register_pc_ = 13;
    VLOG(1) << "[13] hlt";
    HLT();
  }
};

class FickleGhostFactory : public ::GhostFactory {
 public:
  virtual ~FickleGhostFactory() {}

  std::unique_ptr<::GhostInterface> Create() {
    return std::unique_ptr<::GhostInterface>(new FickleGhost());
  }
};

}  // namespace ghost
