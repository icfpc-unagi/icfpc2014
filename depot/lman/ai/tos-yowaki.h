#ifndef LMAN_AI_TOS_YOWAKI_H_
#define LMAN_AI_TOS_YOWAKI_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace tos_yowaki {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace tos_yowaki

class tos_yowakiLambdaMan : public LambdaMan {
 public:
  tos_yowakiLambdaMan() {}
  virtual ~tos_yowakiLambdaMan() {}

  P BInit(P game, P nazo) override {
    return tos_yowaki::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return tos_yowaki::step(ai, game);
  }
};

class tos_yowakiLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~tos_yowakiLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new tos_yowakiLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_TOS_YOWAKI_H_

