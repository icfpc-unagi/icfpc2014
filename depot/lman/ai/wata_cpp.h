#ifndef LMAN_AI_WATA_CPP_H_
#define LMAN_AI_WATA_CPP_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace wata_cpp {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace wata_cpp

class wata_cppLambdaMan : public LambdaMan {
 public:
  wata_cppLambdaMan() {}
  virtual ~wata_cppLambdaMan() {}

  const char* Name() override { return "wata_cpp"; }

  P BInit(P game, P nazo) override {
    return wata_cpp::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return wata_cpp::step(ai, game);
  }
};

class wata_cppLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~wata_cppLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new wata_cppLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_WATA_CPP_H_

