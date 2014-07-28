#ifndef LMAN_AI_CHOKUDAI_33_H_
#define LMAN_AI_CHOKUDAI_33_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_33 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_33

class chokudai_33LambdaMan : public LambdaMan {
 public:
  chokudai_33LambdaMan() {}
  virtual ~chokudai_33LambdaMan() {}

  const char* Name() override { return "chokudai-33"; }

  P BInit(P game, P nazo) override {
    return chokudai_33::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_33::step(ai, game);
  }
};

class chokudai_33LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_33LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_33LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_33_H_

