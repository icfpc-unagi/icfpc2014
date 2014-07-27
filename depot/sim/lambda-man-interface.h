#ifndef SIM_LAMBDA_MAN_INTERFACE_H_
#define SIM_LAMBDA_MAN_INTERFACE_H_

#include "sim/character.h"
#include "sim/game-interface.h"
#include "util/coordinate.h"

// Lambda-Man interface
class LambdaManInterface : public Character {
 public:
  void Init(GameInterface* game) {
    game_ = game;
    Main();
  }
  virtual void Main() = 0;
  virtual int Step() = 0;

 protected:
  GameInterface* game_;
};

// To create a LambdaMan class above
class LambdaManFactory {
 public:
  virtual ~LambdaManFactory() {}
  virtual std::unique_ptr<LambdaManInterface> Create() = 0;
};

#endif  // SIM_LAMBDA_MAN_INTERFACE_H_
