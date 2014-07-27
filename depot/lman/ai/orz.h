#ifndef LMAN_AI_ORZ_H_
#define LMAN_AI_ORZ_H_

#include "lman/lambda-man.h"
#include "sbl/sbl.h"
#include "translator/lib.h"

namespace lman {
namespace orz {

P init(P game, P nazo);
P step(P ai, P game);

}  // namespace orz

class orzLambdaMan : public LambdaMan {
 public:
  orzLambdaMan() {}
  virtual ~orzLambdaMan() {}

  P BInit(P game, P nazo) override {
    return orz::init(game, nazo);
  }

  P BStep(P ai, P game) override {
    return orz::step(ai, game);
  }
};

class orzLambdaManFactory : public ::LambdaManFactory {
 public:
  virtual ~orzLambdaManFactory() {}

  std::unique_ptr<::LambdaManInterface> Create() {
    return std::unique_ptr<::LambdaManInterface>(new orzLambdaMan());
  }
};

}  // namespace lman

#endif  // LMAN_AI_ORZ_H_

