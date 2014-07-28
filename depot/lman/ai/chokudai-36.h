#ifndef LMAN_AI_CHOKUDAI_36_H_
#define LMAN_AI_CHOKUDAI_36_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_36 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_36

class chokudai_36LambdaMan : public LambdaMan {
 public:
  chokudai_36LambdaMan() {}
  virtual ~chokudai_36LambdaMan() {}

  const char* Name() override { return "chokudai-36"; }

  P BInit(P game, P nazo) override {
    return chokudai_36::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_36::step(ai, game);
  }
};

class chokudai_36LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_36LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_36LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_36_H_

