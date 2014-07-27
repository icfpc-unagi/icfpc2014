#ifndef SBL_SBL_H_

#include "sbl/array256.h"

P create_array256_rec(int n) {
  P a;
  if (n == 1) {
    a = top(0);
  } else {
    a = P(create_array256_rec(n / 2), create_array256_rec(n / 2));
  }
  return a;
}

P create_array256() {
  return create_array256_rec(256);
}

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

P create_array2d256_rec(int n) {
  P t;
  if (n == 1) {
    t = create_array256();
  } else {
    t = P(create_array2d256_rec(n / 2), create_array2d256_rec(n / 2));
  }
  return t;
}

P create_array2d256() {
  return create_array2d256_rec(256);
}

P list2d_to_array2d256_rec(P l) {
  P t;
  if (atom(l)) {
    t = top(0);
  } else {
    t = P(list_to_array256(fst(l)), list2d_to_array2d256_rec(snd(l)));
  }
  return t;
}

P list2d_to_array2d256(P l) {
  return list_to_array256(list2d_to_array2d256_rec(l));
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

P get_array2d256(P t, int i, int j) {
  return get_array256(get_array256(t, i), j);
}

#endif  // SBL_SBL_H_
