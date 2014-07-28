#ifndef LMAN_AI_CHOKUDAI_27_H_
#define LMAN_AI_CHOKUDAI_27_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_27 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_27

class chokudai_27LambdaMan : public LambdaMan {
 public:
  chokudai_27LambdaMan() {}
  virtual ~chokudai_27LambdaMan() {}

  const char* Name() override { return "chokudai-27"; }

  P BInit(P game, P nazo) override {
    return chokudai_27::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_27::step(ai, game);
  }
};

class chokudai_27LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_27LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_27LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_27_H_

