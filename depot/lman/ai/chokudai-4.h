#ifndef LMAN_AI_CHOKUDAI_4_H_
#define LMAN_AI_CHOKUDAI_4_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace chokudai_4 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace chokudai_4

class chokudai_4LambdaMan : public LambdaMan {
 public:
  chokudai_4LambdaMan() {}
  virtual ~chokudai_4LambdaMan() {}

  const char* Name() override { return "chokudai-4"; }

  P BInit(P game, P nazo) override {
    return chokudai_4::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return chokudai_4::step(ai, game);
  }
};

class chokudai_4LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~chokudai_4LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new chokudai_4LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_CHOKUDAI_4_H_

