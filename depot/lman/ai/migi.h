#ifndef LMAN_AI_MIGI_H_
#define LMAN_AI_MIGI_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace migi {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace migi

class migiLambdaMan : public LambdaMan {
 public:
  migiLambdaMan() {}
  virtual ~migiLambdaMan() {}

  P BInit(P game, P nazo) override {
    return migi::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return migi::step(ai, game);
  }
};

class migiLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~migiLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new migiLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_MIGI_H_

