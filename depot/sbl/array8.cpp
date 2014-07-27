#ifndef SBL_SBL_H_

#include "sbl/array8.h"

P create_array8_rec(int n) {
  P a;
  if (n == 1) {
    a = top(0);
  } else {
    a = P(create_array8_rec(n / 2), create_array8_rec(n / 2));
  }
  return a;
}

P create_array8() {
  return create_array8_rec(8);
}

P list_to_array8_rec(P t, int size) {
  P tmp;
  if (atom(t)) {
    t = P(0, 0);
  } else {
    if (size > 1) {
      t = list_to_array8_rec(t, size / 2);
      tmp = list_to_array8_rec(snd(t), size / 2);
      t = P(P(fst(t), fst(tmp)), snd(tmp));
    }
  }
  return t;
}

P list_to_array8(P list) {
  return fst(list_to_array8_rec(list, 8));
}

P create_array2d8_rec(int n) {
  P t;
  if (n == 1) {
    t = create_array8();
  } else {
    t = P(create_array2d8_rec(n / 2), create_array2d8_rec(n / 2));
  }
  return t;
}

P create_array2d8() {
  return create_array2d8_rec(8);
}

P list2d_to_array2d8_rec(P l) {
  P t;
  if (atom(l)) {
    t = top(0);
  } else {
    t = P(list_to_array8(fst(l)), list2d_to_array2d8_rec(snd(l)));
  }
  return t;
}

P list2d_to_array2d8(P l) {
  return list_to_array8(list2d_to_array2d8_rec(l));
}

P get_array2d8(P t, int i, int j) {
  return get_array8(get_array8(t, i), j);
}

#endif  // SBL_SBL_H_
