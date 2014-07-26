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
  // TODO: Map
  P m;
  // LambdaMan's status
  P l = P(game_->GetVitality(), P(P(c_, r_), P(d_, P(game_->GetLives(), game_->GetScore()))));
  // TODO: ghosts' status
  P g;
  // TODO: fruits
  P f;
  return P(m, P(l, P(g, f)));
}
