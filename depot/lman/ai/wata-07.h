#ifndef LMAN_AI_WATA_07_H_
#define LMAN_AI_WATA_07_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace wata_07 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace wata_07

class wata_07LambdaMan : public LambdaMan {
 public:
  wata_07LambdaMan() {}
  virtual ~wata_07LambdaMan() {}

  const char* Name() override { return "wata-07"; }

  P BInit(P game, P nazo) override {
    return wata_07::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return wata_07::step(ai, game);
  }
};

class wata_07LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~wata_07LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new wata_07LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_WATA_07_H_

