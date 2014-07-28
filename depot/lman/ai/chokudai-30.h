#ifndef LMAN_AI_CHOKUDAI_30_H_
#define LMAN_AI_CHOKUDAI_30_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_30 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_30

class chokudai_30LambdaMan : public LambdaMan {
 public:
  chokudai_30LambdaMan() {}
  virtual ~chokudai_30LambdaMan() {}

  const char* Name() override { return "chokudai-30"; }

  P BInit(P game, P nazo) override {
    return chokudai_30::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_30::step(ai, game);
  }
};

class chokudai_30LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_30LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_30LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_30_H_

