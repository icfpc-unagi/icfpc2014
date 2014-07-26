#include "translator/lib.h"

Pair::Pair(P a, P d) {
  std::shared_ptr<P> car(new P(a));
  std::shared_ptr<P> cdr(new P(d));
  this->car = car;
  this->cdr = cdr;
}
