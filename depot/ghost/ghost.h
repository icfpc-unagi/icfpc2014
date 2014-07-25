#ifndef GHOST_GHOST_H_
#define GHOST_GHOST_H_

#include <stdint.h>
#include <vector>

#include <glog/logging.h>

#include "base/string-printf.h"
#include "sim/sim.h"

namespace ghost {

class Ghost : public ::GhostInterface {
 public:
  typedef uint8_t Value;

  Ghost();
  virtual ~Ghost();

  int Step() override {
    Run();
    return direction_;
  }

  virtual void Run() = 0;
  void ResetTick() {
    tick_ = 0;
    error_ = false;
    halt_ = false;
  }

  // Returns true iff this Ghost program should exit.
  bool Tick() {
    if (error_ || halt_) return true;
    tick_++;
    return tick_ > 1024;
  }

  Value& Memory(Value src) { return memory_[src]; }

  string Name(const Value& target) {
    int index = &target - &memory_[0];
    if (0 <= index && index < 256) {
      return StringPrintf("memory[%d]", index);
    }
    if (&target == &register_pc_) { return "PC"; }
    if (&target == &register_a_) { return "A"; }
    if (&target == &register_b_) { return "B"; }
    if (&target == &register_c_) { return "C"; }
    if (&target == &register_d_) { return "D"; }
    if (&target == &register_e_) { return "E"; }
    if (&target == &register_f_) { return "F"; }
    if (&target == &register_g_) { return "G"; }
    if (&target == &register_h_) { return "H"; }
    return "<Unknown>";
  }

 protected:
  //////////////////////////////////////////////////////////////////////////////
  // Instructions
  //////////////////////////////////////////////////////////////////////////////

  // Specification:
  //   MOV dest, src
  //     Copy the value of the src argument into the dest argument. dest may
  //     not be a constant.
  void MOV(Value& dest, Value src) {
    VLOG(2) << Name(dest) << " = " << static_cast<int>(src);
    dest = src; 
  }

  // Specification:
  //   INC dest
  //     Add 1 to the value of dest and store the result in dest. dest may not
  //     be a constant or the register PC.
  void INC(Value& dest) {
    VLOG(2) << Name(dest) << " = " << static_cast<int>(dest) << " + 1";
    dest++;
  }

  // Specification:
  //   DEC dest
  //     Subtract 1 from the value of dest and store the result in dest. dest
  //     may not be a constant or the register PC.
  void DEC(Value& dest) {
    VLOG(2) << Name(dest) << " = " << static_cast<int>(dest) << " - 1";
    dest--;
  }

  // Specification:
  //   ADD dest, src
  //     Add the value of src to the value of dest and store the result in
  //     dest. dest may not be a constant or the register PC.
  void ADD(Value& dest, Value src) {
    VLOG(2) << Name(dest) << " = " << static_cast<int>(dest) << " + "
                                   << static_cast<int>(src);
    dest += src;
  }

  // Speicification:
  //   SUB dest, src
  //     Subtract the value of src from the value of dest and store the result
  //     in dest. dest may not be a constant or the register PC.
  void SUB(Value& dest, Value src) { dest -= src; }

  // Specification:
  //   MUL dest, src
  //     Multiply the value of src by the value of dest and store the result in
  //     dest. dest may not be a constant or the register PC.
  void MUL(Value& dest, Value src) { dest *= src; }

  // Speicification:
  //   DIV dest, src
  //     Compute the integer quotient of dest by the value of src, and store
  //     the result in dest. dest may not be a constant or the register PC.
  //     Results in an error if the value of src is 0.
  void DIV(Value& dest, Value src) {
    if (src == 0) {
      error_ = true;
      return;
    }
    dest /= src;
  }

  // Specification:
  //   AND dest, src
  //     Bitwise AND the value of dest and the value of src, storing the result
  //     in dest. dest may not be a constant or the register PC.
  void AND(Value& dest, Value src) { dest &= src; }

  // Specification:
  //   OR dest,src
  //     Bitwise OR the value of dest and the value of src, storing the result
  //     in dest. dest may not be a constant or the register PC.
  void OR(Value& dest, Value src) { dest |= src; }

  // Specification:
  //   XOR dest,src
  //     Bitwise XOR the value of dest and the value of src, storing the result
  //     in dest. dest may not be a constant or the register PC.
  void XOR(Value& dest, Value src) { dest ^= src; }

  // Specification:
  //   JLT targ, x, y
  //     Compare the value of x with the value of y. If the value of x is less
  //     than the value of y, set the PC to the constant value targ.
  bool JLT(Value x, Value y) { return x < y; }

  // Specification:
  //   JEQ targ,x,y
  //     Compare the value of x with the value of y. If the value of x is equal
  //     to the value of y, set the PC to the constant value targ.
  bool JEQ(Value x, Value y) { return x == y; }

  // Specification:
  //   JGT targ,x,y
  //     Compare the value of x with the value of y. If the value of x is
  //     greater than the value of y, set the PC to the constant value targ.
  bool JGT(Value x, Value y) { return x > y; }

  // Specification:
  //   HLT
  //     Halt execution of the GHC.
  void HLT() { halt_ = true; }

  //////////////////////////////////////////////////////////////////////////////
  // Interrupt instructions
  //////////////////////////////////////////////////////////////////////////////

  // Set the direction of the ghost. 0 is up; 1 is right; 2 is down; 3 is left.
  //
  // The direction of the ghost is set at the end of the game cycle. If the
  // interrupt is called multiple times in a single game cycle, the last
  // interrupt overrides any earlier ones. Using an invalid direction in
  // register A is equivalent to retaining the ghost’s original direction at
  // the beginning of the game cycle.
  //
  // INPUT: register_a_ (ghost's new direction)
  void INT0() {}

  // Stores the first Lambda-Man’s position in registers A (x-ordinate) and
  // B (y-ordinate). In the single Lambda-Man version of the game, the first
  // Lambda-Man is the only Lambda-Man.
  //
  // OUTPUT: register_a_ (First Lambda-Man's x-ordinate)
  // OUTPUT: register_b_ (First Lambda-Man's y-ordinate)
  void INT1() {}

  // Stores the second Lambda-Man’s position in registers A (x-ordinate) and
  // B (y-ordinate). In the single Lambda-Man version of the game, the
  // behaviour of this interrupt is unknown.
  //
  // OUTPUT: register_a_ (Second Lambda-Man's x-ordinate)
  // OUTPUT: register_b_ (Second Lambda-Man's y-ordinate)
  void INT2() {}

  // Stores the ghost's index in register A.
  //
  // OUTPUT: register_a_ (this ghost's index)
  void INT3() {}

  // For the ghost with index read from register A, stores its starting
  // position in registers A (x-ordinate) and B (y-ordinate). If A is not a
  // valid ghost index, does nothing.
  //
  // INPUT: register_a_ (ghost index)
  // OUTPUT: register_a_ (indexed ghost's starting x-ordinate)
  // OUTPUT: register_b_ (indexed ghost's starting y-ordinate)
  void INT4() {}

  // For the ghost with index read from register A, stores its current position
  // in registers A (x-ordinate) and B (y-ordinate). If A is not a valid ghost
  // index, does nothing.
  //
  // INPUT: register_a_ (ghost index)
  // OUTPUT: register_a_ (indexed ghost's current x-ordinate)
  // OUTPUT: register_b_ (indexed ghost's current y-ordinate)
  void INT5() {}

  // For the ghost with index read from register A, stores its vitality in
  // register A, and its direction in register B.
  // Vitality: 0: standard; 1: fright mode; 2: invisible.
  // If A is not a valid ghost index, does nothing.
  //
  // INPUT: register_a_ (ghost index)
  // OUTPUT: register_a_ (indexed ghost's current vitality)
  // OUTPUT: register_b_ (indexed ghost's current direction)
  void INT6() {}

  // Stores the current contents of map square with index read from registers A
  // (x-ordinate) and B (y-ordinate) in register A. If the co-ordinates lie
  // outside the defined bounds of the map, stores 0.
  //
  // Contents:
  //   0 - Wall (#)
  //   1 - Empty (<space>)
  //   2 - Pill
  //   3 - Power pill
  //   4 - Fruit
  //   5 - Lambda-Man starting position
  //   6 - Ghost starting position
  //
  // INPUT: register_a_ (map square x-ordinate)
  // INPUT: register_a_ (map square y-ordinate)
  // OUTPUT: register_a_ (contents of map square)
  void INT7() {}

  // Sends the current value of the PC and all registers to an external
  // debug/trace agent.
  //
  // INPUT: all registers
  void INT8() {
    printf("Registers: A (%d), B (%d), C (%d), D(%d), E(%d), F(%d), G(%d), "
           "H(%d), PC(%d)\n",
           register_a_, register_b_, register_c_, register_d_, register_e_,
           register_f_, register_g_, register_h_, register_pc_);
    printf("Current tick: %d\n", tick_);
  }

 protected:
  Value register_pc_;
  Value register_a_;
  Value register_b_;
  Value register_c_;
  Value register_d_;
  Value register_e_;
  Value register_f_;
  Value register_g_;
  Value register_h_;
  bool error_;
  bool halt_;
  int tick_;
  vector<Value> memory_;

  int direction_;
};

}  // namespace ghost

#endif  // GHOST_GHOST_H_
