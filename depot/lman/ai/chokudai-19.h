#ifndef LMAN_AI_CHOKUDAI_19_H_
#define LMAN_AI_CHOKUDAI_19_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_19 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_19

class chokudai_19LambdaMan : public LambdaMan {
 public:
  chokudai_19LambdaMan() {}
  virtual ~chokudai_19LambdaMan() {}

  const char* Name() override { return "chokudai-19"; }

  P BInit(P game, P nazo) override {
    return chokudai_19::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_19::step(ai, game);
  }
};

class chokudai_19LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_19LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_19LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_19_H_

