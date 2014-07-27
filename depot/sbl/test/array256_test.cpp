#include "translator/lib.h"
#include "sbl/list.h"
#include "array256.h"

void test_array(int n) {
  int i;
  P l;
  P t;
  l = top(0);

  i = n;
  while (i > 0) {
    l = P(i * 100, l);
    i -= 1;
  }
  debug(l);

  t = list_to_array256(l);
  debug(t);

  i = 0;
  while (i < n) {
    debug(get_array256(t, i));
    i += 1;
  }
}

void run() {
  test_array(256);
}