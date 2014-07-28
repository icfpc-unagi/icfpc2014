#ifndef LMAN_AI_CHOKUDAI_22_H_
#define LMAN_AI_CHOKUDAI_22_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_22 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_22

class chokudai_22LambdaMan : public LambdaMan {
 public:
  chokudai_22LambdaMan() {}
  virtual ~chokudai_22LambdaMan() {}

  const char* Name() override { return "chokudai-22"; }

  P BInit(P game, P nazo) override {
    return chokudai_22::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_22::step(ai, game);
  }
};

class chokudai_22LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_22LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_22LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_22_H_

