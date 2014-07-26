#ifndef LMAN_AI_CHOKUDAI_10_H_
#define LMAN_AI_CHOKUDAI_10_H_

#include "translator/lib.h"
#include "sbl/tree.cpp"

namespace lman {
namespace chokudai_10 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_10

class chokudai_10LambdaMan {
 public:
  P BInit(P game, P nazo) {
    return chokudai_10::init(game, nazo);
  }

  P BStep(P ai, P game) {
    return chokudai_10::step(ai, game);
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_10_H_
