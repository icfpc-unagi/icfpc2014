#ifndef LMAN_AI_CHOKUDAI_24_H_
#define LMAN_AI_CHOKUDAI_24_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_24 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_24

class chokudai_24LambdaMan : public LambdaMan {
 public:
  chokudai_24LambdaMan() {}
  virtual ~chokudai_24LambdaMan() {}

  const char* Name() override { return "chokudai-24"; }

  P BInit(P game, P nazo) override {
    return chokudai_24::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_24::step(ai, game);
  }
};

class chokudai_24LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_24LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_24LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_24_H_

