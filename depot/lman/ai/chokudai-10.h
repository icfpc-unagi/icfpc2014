#ifndef LMAN_AI_CHOKUDAI_10_H_
#define LMAN_AI_CHOKUDAI_10_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_10 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_10

class chokudai_10LambdaMan : public LambdaMan {
 public:
  chokudai_10LambdaMan() {}
  virtual ~chokudai_10LambdaMan() {}

  P BInit(P game, P nazo) override {
    return chokudai_10::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_10::step(ai, game);
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_10_H_

