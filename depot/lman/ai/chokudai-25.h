#ifndef LMAN_AI_CHOKUDAI_25_H_
#define LMAN_AI_CHOKUDAI_25_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_25 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_25

class chokudai_25LambdaMan : public LambdaMan {
 public:
  chokudai_25LambdaMan() {}
  virtual ~chokudai_25LambdaMan() {}

  const char* Name() override { return "chokudai-25"; }

  P BInit(P game, P nazo) override {
    return chokudai_25::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_25::step(ai, game);
  }
};

class chokudai_25LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_25LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_25LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_25_H_

