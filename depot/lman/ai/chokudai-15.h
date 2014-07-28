#ifndef LMAN_AI_CHOKUDAI_15_H_
#define LMAN_AI_CHOKUDAI_15_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_15 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_15

class chokudai_15LambdaMan : public LambdaMan {
 public:
  chokudai_15LambdaMan() {}
  virtual ~chokudai_15LambdaMan() {}

  const char* Name() override { return "chokudai-15"; }

  P BInit(P game, P nazo) override {
    return chokudai_15::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_15::step(ai, game);
  }
};

class chokudai_15LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_15LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_15LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_15_H_

