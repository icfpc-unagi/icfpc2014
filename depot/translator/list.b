// vi:filetype=cpp:
#include "lib.h"

P readList(P list, int n) {
  P res;
  if (n == 0) {
    res = fst(list);
  } else {
    res = readList(list, n-1);
  }
  return res;
}

P writeList(P list, int n, P val) {
  P res;
  if (n == 0) {
    res = P(val, snd(list));
  } else {
    res = P(
	fst(list),
	writeList(snd(list), n-1, val) );
  }
  return res;
}

// read list[i][j]
P readList2(P list, int i, int j) {
  return readList(readList(list, i), j);
}

// write list[i][j]
P writeList2(P list, int i, int j, P val) {
  return writeList(list, i, writeList(readList(list,i), j, val) );
}

int length(P list) {
  int res;
  if (atom(list)) {
    res = 0;
  } else {
    res = 1 + length(snd(list));
  }
  return res;
}

