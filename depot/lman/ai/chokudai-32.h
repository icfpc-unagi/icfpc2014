#ifndef LMAN_AI_CHOKUDAI_32_H_
#define LMAN_AI_CHOKUDAI_32_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_32 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_32

class chokudai_32LambdaMan : public LambdaMan {
 public:
  chokudai_32LambdaMan() {}
  virtual ~chokudai_32LambdaMan() {}

  const char* Name() override { return "chokudai-32"; }

  P BInit(P game, P nazo) override {
    return chokudai_32::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_32::step(ai, game);
  }
};

class chokudai_32LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_32LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_32LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_32_H_

