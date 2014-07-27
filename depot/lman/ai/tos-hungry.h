#ifndef LMAN_AI_TOS_HUNGRY_H_
#define LMAN_AI_TOS_HUNGRY_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace tos_hungry {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace tos_hungry

class tos_hungryLambdaMan : public LambdaMan {
 public:
  tos_hungryLambdaMan() {}
  virtual ~tos_hungryLambdaMan() {}

  const char* Name() override { return "tos-hungry"; }

  P BInit(P game, P nazo) override {
    return tos_hungry::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return tos_hungry::step(ai, game);
  }
};

class tos_hungryLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~tos_hungryLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new tos_hungryLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_TOS_HUNGRY_H_

