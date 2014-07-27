#ifndef SBL_SBL_H_

#include "sbl/array256.h"

P get_array256(P t, int i) {
  int n = 128;
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

int set_array2d256_rec_j;

P set_array2d256_rec(P t, int i, P v, int n) {
  if (n == 0) {
    t = set_array256(t, set_array2d256_rec_j, v);
  } else {
    if (i < n) {
      t = P(set_array2d256_rec(fst(t), i, v, n / 2), snd(t));
    } else {
      t = P(fst(t), set_array2d256_rec(snd(t), i - n, v, n / 2));
    }
  }
  return t;
}

P set_array2d256(P t, int i, int j, P v) {
  set_array2d256_rec_j = j;
  return set_array2d256_rec(t, i, v, 128);
}

#endif  // SBL_SBL_H_
