#ifndef LMAN_AI_CHOKUDAI_8_H_
#define LMAN_AI_CHOKUDAI_8_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_8 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_8

class chokudai_8LambdaMan : public LambdaMan {
 public:
  chokudai_8LambdaMan() {}
  virtual ~chokudai_8LambdaMan() {}

  P BInit(P game, P nazo) override {
    return chokudai_8::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_8::step(ai, game);
  }
};

class chokudai_8LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_8LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_8LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_8_H_

