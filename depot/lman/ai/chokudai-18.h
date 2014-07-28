#ifndef LMAN_AI_CHOKUDAI_18_H_
#define LMAN_AI_CHOKUDAI_18_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_18 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_18

class chokudai_18LambdaMan : public LambdaMan {
 public:
  chokudai_18LambdaMan() {}
  virtual ~chokudai_18LambdaMan() {}

  const char* Name() override { return "chokudai-18"; }

  P BInit(P game, P nazo) override {
    return chokudai_18::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_18::step(ai, game);
  }
};

class chokudai_18LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_18LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_18LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_18_H_

