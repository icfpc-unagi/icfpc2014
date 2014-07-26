#ifndef LMAN_LAMBDA_MAN_H_
#define LMAN_LAMBDA_MAN_H_

#include <vector>

#include "sim/lambda-man-interface.h"
#include "translator/lib.h"

namespace lman {

class LambdaMan : public ::LambdaManInterface {
 public:
  LambdaMan();
  virtual ~LambdaMan();

  void Main() override;
  int Step() override;

 private:
  virtual P BInit(P game, P nazo) = 0;
  virtual P BStep(P ai, P game) = 0;

  static P MakeList(const vector<P>& t);
  P EncodeWorld() const;
  P EncodeGhost(int ghost_index) const;
  
  P state_;
};

}  // namespace lman

#endif  // LMAN_LAMBDA_MAN_H_
