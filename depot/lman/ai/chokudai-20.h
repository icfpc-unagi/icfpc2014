#ifndef LMAN_AI_CHOKUDAI_20_H_
#define LMAN_AI_CHOKUDAI_20_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_20 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_20

class chokudai_20LambdaMan : public LambdaMan {
 public:
  chokudai_20LambdaMan() {}
  virtual ~chokudai_20LambdaMan() {}

  const char* Name() override { return "chokudai-20"; }

  P BInit(P game, P nazo) override {
    return chokudai_20::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_20::step(ai, game);
  }
};

class chokudai_20LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_20LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_20LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_20_H_

