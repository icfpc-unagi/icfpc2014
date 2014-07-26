#include "lman/lman.h"
#include "sim/sim.h"
#include "util/coordinate.h"

void LambdaManImpl::Main() {
  P game = EncodeWorld();
  P nazo;
  P ret = init(game, nazo);
  state_ = fst(ret);
}

int LambdaManImpl::Step() {
  P game = EncodeWorld();
  P ret = step(state_, game);
  state_ = fst(ret);
  return toi(snd(ret));
}

P LambdaManImpl::EncodeWorld() {
  P m;  // TODO
  P l;  // TODO
  P g;  // TODO
  P f;  // TODO
  return P(m, P(l, P(g, f)));
}
