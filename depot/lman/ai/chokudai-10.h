#ifndef LMAN_AI_CHOKUDAI_10_H_
#define LMAN_AI_CHOKUDAI_10_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_10 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_10

class chokudai_10LambdaMan : public LambdaMan {
 public:
  chokudai_10LambdaMan() {}
  virtual ~chokudai_10LambdaMan() {}

  const char* Name() override { return "chokudai-10"; }

  P BInit(P game, P nazo) override {
    return chokudai_10::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_10::step(ai, game);
  }
};

class chokudai_10LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_10LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_10LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_10_H_

