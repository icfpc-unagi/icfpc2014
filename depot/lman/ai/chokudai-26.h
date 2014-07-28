#ifndef LMAN_AI_CHOKUDAI_26_H_
#define LMAN_AI_CHOKUDAI_26_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_26 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_26

class chokudai_26LambdaMan : public LambdaMan {
 public:
  chokudai_26LambdaMan() {}
  virtual ~chokudai_26LambdaMan() {}

  const char* Name() override { return "chokudai-26"; }

  P BInit(P game, P nazo) override {
    return chokudai_26::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_26::step(ai, game);
  }
};

class chokudai_26LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_26LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_26LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_26_H_

