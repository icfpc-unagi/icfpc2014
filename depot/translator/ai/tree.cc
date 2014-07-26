#include "tree.b"

P step(P state, P game) {
  int dir = 0;  // 1, 2, 3
  return P(state, dir);
}

P init(P game, P nazo) {
  return P(0, 0);
}
