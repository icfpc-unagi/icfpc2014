#ifndef LMAN_AI_CHOKUDAI_35_H_
#define LMAN_AI_CHOKUDAI_35_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_35 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_35

class chokudai_35LambdaMan : public LambdaMan {
 public:
  chokudai_35LambdaMan() {}
  virtual ~chokudai_35LambdaMan() {}

  const char* Name() override { return "chokudai-35"; }

  P BInit(P game, P nazo) override {
    return chokudai_35::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_35::step(ai, game);
  }
};

class chokudai_35LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_35LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_35LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_35_H_

