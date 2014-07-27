#ifndef LMAN_AI_TOS_SOKUSHI_KAIHI_H_
#define LMAN_AI_TOS_SOKUSHI_KAIHI_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace tos_sokushi_kaihi {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace tos_sokushi_kaihi

class tos_sokushi_kaihiLambdaMan : public LambdaMan {
 public:
  tos_sokushi_kaihiLambdaMan() {}
  virtual ~tos_sokushi_kaihiLambdaMan() {}

  P BInit(P game, P nazo) override {
    return tos_sokushi_kaihi::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return tos_sokushi_kaihi::step(ai, game);
  }
};

class tos_sokushi_kaihiLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~tos_sokushi_kaihiLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new tos_sokushi_kaihiLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_TOS_SOKUSHI_KAIHI_H_

