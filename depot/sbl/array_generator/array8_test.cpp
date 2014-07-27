#include "translator/lib.h"
#include "sbl/list.h"
#include "array8.h"

void test_array(n) {
  int i;
  P l;
  P t;
  l = top(0);

  i = n;
  while (i < n) {
    l = P(i * 100, l);
    i -= 1;
  }

  t = list_to_array8(l);
  debug(t);

  i = 0;
  while (i < n) {
    debug(get_array8(t, i));
    i += 1;
  }
}

void run() {
  test_array(8);
}
