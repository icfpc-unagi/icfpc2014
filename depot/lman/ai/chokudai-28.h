#ifndef LMAN_AI_CHOKUDAI_28_H_
#define LMAN_AI_CHOKUDAI_28_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_28 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_28

class chokudai_28LambdaMan : public LambdaMan {
 public:
  chokudai_28LambdaMan() {}
  virtual ~chokudai_28LambdaMan() {}

  const char* Name() override { return "chokudai-28"; }

  P BInit(P game, P nazo) override {
    return chokudai_28::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_28::step(ai, game);
  }
};

class chokudai_28LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_28LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_28LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_28_H_

