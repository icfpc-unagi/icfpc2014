#ifndef LMAN_AI_CHOKUDAI_12_H_
#define LMAN_AI_CHOKUDAI_12_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_12 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_12

class chokudai_12LambdaMan : public LambdaMan {
 public:
  chokudai_12LambdaMan() {}
  virtual ~chokudai_12LambdaMan() {}

  P BInit(P game, P nazo) override {
    return chokudai_12::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_12::step(ai, game);
  }
};

class chokudai_12LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_12LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_12LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_12_H_

