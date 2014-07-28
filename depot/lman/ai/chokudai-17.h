#ifndef LMAN_AI_CHOKUDAI_17_H_
#define LMAN_AI_CHOKUDAI_17_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_17 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_17

class chokudai_17LambdaMan : public LambdaMan {
 public:
  chokudai_17LambdaMan() {}
  virtual ~chokudai_17LambdaMan() {}

  const char* Name() override { return "chokudai-17"; }

  P BInit(P game, P nazo) override {
    return chokudai_17::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_17::step(ai, game);
  }
};

class chokudai_17LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_17LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_17LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_17_H_

