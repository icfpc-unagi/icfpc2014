#ifndef LMAN_AI_TOS1_H_
#define LMAN_AI_TOS1_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace tos1 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace tos1

class tos1LambdaMan : public LambdaMan {
 public:
  tos1LambdaMan() {}
  virtual ~tos1LambdaMan() {}

  const char* Name() override { return "tos1"; }

  P BInit(P game, P nazo) override {
    return tos1::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return tos1::step(ai, game);
  }
};

class tos1LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~tos1LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new tos1LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_TOS1_H_

