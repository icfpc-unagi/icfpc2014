#ifndef SBL_SBL_H_

#include "sbl/array256.h"

P list_to_array256_rec(P t, int size) {
  P tmp;
  if (atom(t)) {
    t = P(0, 0);
  } else {
    if (size > 1) {
      t = list_to_array256_rec(t, size / 2);
      tmp = list_to_array256_rec(snd(t), size / 2);
      t = P(P(fst(t), fst(tmp)), snd(tmp));
    }
  }
  return t;
}

P list_to_array256(P list) {
  return fst(list_to_array256_rec(list, 256));
}

P set_array256_rec(P t, int i, P v, int n) {
  if (n == 0) {
    t = v;
  } else {
    if (i < n) {
      t = P(set_array256_rec(fst(t), i, v, n / 2), snd(t));
    } else {
      t = P(fst(t), set_array256_rec(snd(t), i - n, v, n / 2));
    }
  }
  return t;
}

P set_array256(P t, int i, P v) {
  return set_array256_rec(t, i, v, 128);
}

#endif  // SBL_SBL_H_
