#ifndef LMAN_AI_CHOKUDAI_21_H_
#define LMAN_AI_CHOKUDAI_21_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_21 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_21

class chokudai_21LambdaMan : public LambdaMan {
 public:
  chokudai_21LambdaMan() {}
  virtual ~chokudai_21LambdaMan() {}

  const char* Name() override { return "chokudai-21"; }

  P BInit(P game, P nazo) override {
    return chokudai_21::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_21::step(ai, game);
  }
};

class chokudai_21LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_21LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_21LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_21_H_

