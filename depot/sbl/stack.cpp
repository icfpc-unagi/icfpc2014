#ifndef SBL_SBL_H_

#include "sbl/stack.h"

P create_stack() {
  return top(0);
}

int is_empty_stack(P stack) {
  return atom(stack);
}

P push_stack(P stack, P x) {
  return P(x, stack);
}

P top_stack(P stack) {
  return fst(stack);
}

P pop_stack(P stack) {
  return snd(stack);
}

#endif  // SBL_SBL_H_
