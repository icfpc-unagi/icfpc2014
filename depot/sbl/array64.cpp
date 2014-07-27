#ifndef SBL_SBL_H_

#include "sbl/array64.h"

P create_array64_rec(int n) {
  P a;
  if (n == 1) {
    a = top(0);
  } else {
    a = P(create_array64_rec(n / 2), create_array64_rec(n / 2));
  }
  return a;
}

P create_array64() {
  return create_array64_rec(64);
}

P list_to_array64_rec(P t, int size) {
  P tmp;
  if (atom(t)) {
    t = P(0, 0);
  } else {
    if (size > 1) {
      t = list_to_array64_rec(t, size / 2);
      tmp = list_to_array64_rec(snd(t), size / 2);
      t = P(P(fst(t), fst(tmp)), snd(tmp));
    }
  }
  return t;
}

P list_to_array64(P list) {
  return fst(list_to_array64_rec(list, 64));
}

P create_array2d64_rec(int n) {
  P t;
  if (n == 1) {
    t = create_array64();
  } else {
    t = P(create_array2d64_rec(n / 2), create_array2d64_rec(n / 2));
  }
  return t;
}

P create_array2d64() {
  return create_array2d64_rec(64);
}

P list2d_to_array2d64_rec(P l) {
  P t;
  if (atom(l)) {
    t = top(0);
  } else {
    t = P(list_to_array64(fst(l)), list2d_to_array2d64_rec(snd(l)));
  }
  return t;
}

P list2d_to_array2d64(P l) {
  return list_to_array64(list2d_to_array2d64_rec(l));
}

P get_array2d64(P t, int i, int j) {
  return get_array64(get_array64(t, i), j);
}

#endif  // SBL_SBL_H_
