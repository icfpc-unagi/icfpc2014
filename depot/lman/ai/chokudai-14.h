#ifndef LMAN_AI_CHOKUDAI_14_H_
#define LMAN_AI_CHOKUDAI_14_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_14 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_14

class chokudai_14LambdaMan : public LambdaMan {
 public:
  chokudai_14LambdaMan() {}
  virtual ~chokudai_14LambdaMan() {}

  const char* Name() override { return "chokudai-14"; }

  P BInit(P game, P nazo) override {
    return chokudai_14::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_14::step(ai, game);
  }
};

class chokudai_14LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_14LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_14LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_14_H_

