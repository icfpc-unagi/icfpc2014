#ifndef LMAN_AI_TOS2_H_
#define LMAN_AI_TOS2_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace tos2 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace tos2

class tos2LambdaMan : public LambdaMan {
 public:
  tos2LambdaMan() {}
  virtual ~tos2LambdaMan() {}

  const char* Name() override { return "tos2"; }

  P BInit(P game, P nazo) override {
    return tos2::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return tos2::step(ai, game);
  }
};

class tos2LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~tos2LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new tos2LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_TOS2_H_

