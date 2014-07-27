#include "translator/lib.h"
#include "sbl/list.h"
#include "array8.h"

void test_array8() {
  P l;
  P t;
  l = P(100, P(200, P(300, P(400, P(500, P(600, P(700, P(800, 0))))))));
  t = list_to_array8(l);
  debug(t);
  debug(get_array8(t, 0));
  debug(get_array8(t, 1));
  debug(get_array8(t, 2));
  debug(get_array8(t, 3));
  debug(get_array8(t, 4));
  debug(get_array8(t, 5));
  debug(get_array8(t, 6));
  debug(get_array8(t, 7));
}

void run() {
  test_array8();
}
