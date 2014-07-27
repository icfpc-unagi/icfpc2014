#ifndef LMAN_AI_ROUNDING_H_
#define LMAN_AI_ROUNDING_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace rounding {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace rounding

class roundingLambdaMan : public LambdaMan {
 public:
  roundingLambdaMan() {}
  virtual ~roundingLambdaMan() {}

  const char* Name() override { return "rounding"; }

  P BInit(P game, P nazo) override {
    return rounding::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return rounding::step(ai, game);
  }
};

class roundingLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~roundingLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new roundingLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_ROUNDING_H_

