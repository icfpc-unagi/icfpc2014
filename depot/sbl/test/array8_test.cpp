#include "translator/lib.h"
#include "sbl/list.h"
#include "sbl/array8.h"

P generate_list(int n) {
  int i;
  P l;
  l = top(0);
  i = n;
  while (i > 0) {
    l = P(i * 100, l);
    i -= 1;
  }
  return l;
}

P generate_list2d(int m, int n) {
  int i, j;
  P l, l2;
  l2 = top(0);
  i = m;
  while (i > 0) {
    j = n;
    l = top(0);
    while (j > 0) {
      l = P(i * 1000 + j, l);
      j -= 1;
    }
    l2 = P(l, l2);
    i -= 1;
  }
  return l2;
}

void test_array(int n) {
  int i;
  P l;
  P t;
  l = generate_list(n);
  debug(l);

  t = list_to_array8(l);
  debug(t);

  i = 0;
  while (i < n) {
    debug(get_array8(t, i));
    i += 1;
  }
}

void test_array2(int n) {
  P a;
  int i;

  a = create_array8();
  debug(a);

  i = 0;
  while (i < n) {
    a = set_array8(a, i, (i + 1) * 10000);
    i += 1;
  }
  debug(a);

  i = 0;
  while (i < n) {
    debug(get_array8(a, i));
    i += 1;
  }
}

void test_array3(int n) {
  P a;
  int i, j;

  a = create_array2d8();
  debug(a);

  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      a = set_array2d8(a, i, j, (i + 1) * 1000 + (j + 1));
      j += 1;
    }
    i += 1;
  }
  debug(a);

  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      debug(P(P(i, j), get_array2d8(a, i, j)));
      j += 1;
    }
    i += 1;
  }
}

void test_array4(int n, int m) {
  P l, a;
  int i, j;
  l = generate_list2d(n, m);
  debug(l);

  a = list2d_to_array2d8(l);
  debug(a);

  i = 0;
  while (i < n) {
    j = 0;
    while (j < m) {
      debug(P(P(i, j), get_array2d8(a, i, j)));
      j += 1;
    }
    i += 1;
  }
}

void run() {
  test_array(8);
  test_array2(8);
  test_array3(8);
  test_array4(8, 8);

  test_array(1);
  test_array(2);
  test_array(3);
  test_array(5);
  test_array(7);

  test_array4(1, 1);
  test_array4(3, 3);
  test_array4(4, 4);
}
