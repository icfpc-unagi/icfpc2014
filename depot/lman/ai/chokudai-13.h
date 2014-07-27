#ifndef LMAN_AI_CHOKUDAI_13_H_
#define LMAN_AI_CHOKUDAI_13_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_13 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_13

class chokudai_13LambdaMan : public LambdaMan {
 public:
  chokudai_13LambdaMan() {}
  virtual ~chokudai_13LambdaMan() {}

  P BInit(P game, P nazo) override {
    return chokudai_13::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_13::step(ai, game);
  }
};

class chokudai_13LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_13LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_13LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_13_H_

