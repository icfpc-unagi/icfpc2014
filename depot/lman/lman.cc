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
  // Map
  const auto& maze = game_->GetMaze();
  vector<P> ms;
  for (int r = 0; r < maze.size(); ++r) {
    vector<P> line;
    for (int c = 0; c < maze[r].size(); ++c) {
      int cell;
      switch (maze[r][c]) {
        case '#': cell = 0; break;
        case ' ': cell = 1; break;
        case '.': cell = 2; break;
        case 'o': cell = 3; break;
        case '%': cell = 4; break;
        case '\\':cell = 5; break;
        case '=': cell = 6; break;
      }
      line.push_back(cell);
    }
    ms.push_back(MakeList(line));
  }
  P m = MakeList(ms);
  // LambdaMan's status
  P l = P(game_->GetVitality(), P(P(c_, r_), P(d_, P(game_->GetLives(), game_->GetScore()))));
  // ghosts' status
  vector<P> gs;
  for (int i = 0; i < game_->GetNumberOfGhosts(); ++i) {
    gs.push_back(EncodeGhost(i));
  }
  P g = MakeList(gs);
  // TODO: fruits
  P f(0);
  return P(m, P(l, P(g, f)));
}

P LambdaManImpl::EncodeGhost(int ghost_index) const {
  auto rc = game_->GetGhostRC(ghost_index);
  return P(game_->GetGhostVitality(ghost_index), P(P(rc.first, rc.second), game_->GetGhostDirection(ghost_index)));
}
