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

P LambdaManImpl::MakeList(const vector<P>& t) {
  CHECK(!t.empty());
  P tuple = t.back();
  for (int i = t.size() - 2; i >= 0; --i) {
    tuple = P(t[i], tuple);
  }
  return tuple;
}

P LambdaManImpl::EncodeWorld() const {
  // TODO: Map
  P m;
  // LambdaMan's status
  P l = P(game_->GetVitality(), P(P(c_, r_), P(d_, P(game_->GetLives(), game_->GetScore()))));
  // TODO: ghosts' status
  vector<P> g;
  for (int i = 0; i < game_->GetNumberOfGhosts(); ++i) {
    g.push_back(EncodeGhost(i));
  }
  // TODO: fruits
  P f;
  return P(m, P(l, P(MakeList(g), f)));
}

P LambdaManImpl::EncodeGhost(int ghost_index) const {
  auto rc = game_->GetGhostRC(ghost_index);
  return P(game_->GetGhostVitality(ghost_index), P(P(rc.first, rc.second), game_->GetGhostDirection(ghost_index)));
}
