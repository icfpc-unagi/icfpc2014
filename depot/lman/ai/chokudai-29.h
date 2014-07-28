#ifndef LMAN_AI_CHOKUDAI_29_H_
#define LMAN_AI_CHOKUDAI_29_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_29 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_29

class chokudai_29LambdaMan : public LambdaMan {
 public:
  chokudai_29LambdaMan() {}
  virtual ~chokudai_29LambdaMan() {}

  const char* Name() override { return "chokudai-29"; }

  P BInit(P game, P nazo) override {
    return chokudai_29::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_29::step(ai, game);
  }
};

class chokudai_29LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_29LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_29LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_29_H_

