#include "translator/lib.h"
#include "sbl/list.h"
#include "sbl/array<%=n%>.h"

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

  t = list_to_array<%=n%>(l);
  debug(t);

  i = 0;
  while (i < n) {
    debug(get_array<%=n%>(t, i));
    i += 1;
  }
}

void test_array2(int n) {
  P a;
  int i;

  a = create_array<%=n%>();
  debug(a);

  i = 0;
  while (i < n) {
    a = set_array<%=n%>(a, i, (i + 1) * 10000);
    i += 1;
  }
  debug(a);

  i = 0;
  while (i < n) {
    debug(get_array<%=n%>(a, i));
    i += 1;
  }
}

void test_array3(int n) {
  P a;
  int i, j;

  a = create_array2d<%=n%>();
  debug(a);

  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      a = set_array2d<%=n%>(a, i, j, (i + 1) * 1000 + (j + 1));
      j += 1;
    }
    i += 1;
  }
  debug(a);

  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      debug(P(P(i, j), get_array2d<%=n%>(a, i, j)));
      j += 1;
    }
    i += 1;
  }

  // i = 0;
  // while (i < n) {
  //   a = set_array<%=n%>(a, i, (i + 1) * 10000);
  //   i += 1;
  // }
  // debug(a);

  // i = 0;
  // while (i < n) {
  //   debug(get_array<%=n%>(a, i));
  //   i += 1;
  // }
}


void run() {
  test_array(<%=n%>);
  test_array2(<%=n%>);
  test_array3(<%=n%>);
}
