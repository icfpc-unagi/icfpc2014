#ifndef LMAN_AI_WATA_05_H_
#define LMAN_AI_WATA_05_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace wata_05 {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace wata_05

class wata_05LambdaMan : public LambdaMan {
 public:
  wata_05LambdaMan() {}
  virtual ~wata_05LambdaMan() {}

  const char* Name() override { return "wata-05"; }

  P BInit(P game, P nazo) override {
    return wata_05::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return wata_05::step(ai, game);
  }
};

class wata_05LambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~wata_05LambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new wata_05LambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_WATA_05_H_

