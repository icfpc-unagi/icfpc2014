#ifndef LMAN_AI_CHOKUDAI_23_H_
#define LMAN_AI_CHOKUDAI_23_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_23 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_23

class chokudai_23LambdaMan : public LambdaMan {
 public:
  chokudai_23LambdaMan() {}
  virtual ~chokudai_23LambdaMan() {}

  const char* Name() override { return "chokudai-23"; }

  P BInit(P game, P nazo) override {
    return chokudai_23::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_23::step(ai, game);
  }
};

class chokudai_23LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_23LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_23LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_23_H_

