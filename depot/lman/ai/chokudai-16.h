#ifndef LMAN_AI_CHOKUDAI_16_H_
#define LMAN_AI_CHOKUDAI_16_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_16 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_16

class chokudai_16LambdaMan : public LambdaMan {
 public:
  chokudai_16LambdaMan() {}
  virtual ~chokudai_16LambdaMan() {}

  const char* Name() override { return "chokudai-16"; }

  P BInit(P game, P nazo) override {
    return chokudai_16::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_16::step(ai, game);
  }
};

class chokudai_16LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_16LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_16LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_16_H_

