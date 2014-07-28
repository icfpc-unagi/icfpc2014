#ifndef LMAN_AI_CHOKUDAI_34_H_
#define LMAN_AI_CHOKUDAI_34_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_34 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_34

class chokudai_34LambdaMan : public LambdaMan {
 public:
  chokudai_34LambdaMan() {}
  virtual ~chokudai_34LambdaMan() {}

  const char* Name() override { return "chokudai-34"; }

  P BInit(P game, P nazo) override {
    return chokudai_34::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_34::step(ai, game);
  }
};

class chokudai_34LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_34LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_34LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_34_H_

