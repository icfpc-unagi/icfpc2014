#ifndef SBL_SBL_H_

#include "sbl/array64.h"

P get_array64(P t, int i) {
  int n = 32;
  while (n > 0) {
    if (i < n) {
      t = fst(t);
    } else {
      t = snd(t);
      i -= n;
    }
    n = n / 2;
  }
  return t;
}

P set_array64_rec(P t, int i, P v, int n) {
  if (n == 0) {
    t = v;
  } else {
    if (i < n) {
      t = P(set_array64_rec(fst(t), i, v, n / 2), snd(t));
    } else {
      t = P(fst(t), set_array64_rec(snd(t), i - n, v, n / 2));
    }
  }
  return t;
}

P set_array64(P t, int i, P v) {
  return set_array64_rec(t, i, v, 32);
}

int set_array2d64_rec_j;

P set_array2d64_rec(P t, int i, P v, int n) {
  if (n == 0) {
    t = set_array64(t, set_array2d64_rec_j, v);
  } else {
    if (i < n) {
      t = P(set_array2d64_rec(fst(t), i, v, n / 2), snd(t));
    } else {
      t = P(fst(t), set_array2d64_rec(snd(t), i - n, v, n / 2));
    }
  }
  return t;
}

P set_array2d64(P t, int i, int j, P v) {
  set_array2d64_rec_j = j;
  return set_array2d64_rec(t, i, v, 32);
}

#endif  // SBL_SBL_H_
