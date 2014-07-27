#ifndef LMAN_AI_PIYO_H_
#define LMAN_AI_PIYO_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace piyo {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace piyo

class piyoLambdaMan : public LambdaMan {
 public:
  piyoLambdaMan() {}
  virtual ~piyoLambdaMan() {}

  const char* Name() override { return "piyo"; }

  P BInit(P game, P nazo) override {
    return piyo::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return piyo::step(ai, game);
  }
};

class piyoLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~piyoLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new piyoLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_PIYO_H_

