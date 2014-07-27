#ifndef SBL_SBL_H_

#include "sbl/array16.h"

P create_array16_rec(int n) {
  P a;
  if (n == 1) {
    a = top(0);
  } else {
    a = P(create_array16_rec(n / 2), create_array16_rec(n / 2));
  }
  return a;
}

P create_array16() {
  return create_array16_rec(16);
}

P list_to_array16_rec(P t, int size) {
  P tmp;
  if (atom(t)) {
    t = P(0, 0);
  } else {
    if (size > 1) {
      t = list_to_array16_rec(t, size / 2);
      tmp = list_to_array16_rec(snd(t), size / 2);
      t = P(P(fst(t), fst(tmp)), snd(tmp));
    }
  }
  return t;
}

P list_to_array16(P list) {
  return fst(list_to_array16_rec(list, 16));
}

P create_array2d16_rec(int n) {
  P t;
  if (n == 1) {
    t = create_array16();
  } else {
    t = P(create_array2d16_rec(n / 2), create_array2d16_rec(n / 2));
  }
  return t;
}

P create_array2d16() {
  return create_array2d16_rec(16);
}

P list2d_to_array2d16_rec(P l) {
  P t;
  if (atom(l)) {
    t = top(0);
  } else {
    t = P(list_to_array16(fst(l)), list2d_to_array2d16_rec(snd(l)));
  }
  return t;
}

P list2d_to_array2d16(P l) {
  return list_to_array16(list2d_to_array2d16_rec(l));
}

P get_array2d16(P t, int i, int j) {
  return get_array16(get_array16(t, i), j);
}

#endif  // SBL_SBL_H_
