#ifndef LMAN_AI_WATA_10_H_
#define LMAN_AI_WATA_10_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace wata_10 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace wata_10

class wata_10LambdaMan : public LambdaMan {
 public:
  wata_10LambdaMan() {}
  virtual ~wata_10LambdaMan() {}

  const char* Name() override { return "wata-10"; }

  P BInit(P game, P nazo) override {
    return wata_10::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return wata_10::step(ai, game);
  }
};

class wata_10LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~wata_10LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new wata_10LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_WATA_10_H_

