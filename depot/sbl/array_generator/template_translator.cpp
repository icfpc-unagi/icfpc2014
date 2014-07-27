#ifndef SBL_SBL_H_

#include "sbl/array<%=n%>.h"

P get_array<%=n%>(P t, int i) {
  int n = <%= n / 2 %>;
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

P set_array<%=n%>_rec(P t, int i, P v, int n) {
  if (n == 0) {
    t = v;
  } else {
    if (i < n) {
      t = P(set_array<%=n%>_rec(fst(t), i, v, n / 2), snd(t));
    } else {
      t = P(fst(t), set_array<%=n%>_rec(snd(t), i - n, v, n / 2));
    }
  }
  return t;
}

P set_array<%=n%>(P t, int i, P v) {
  return set_array<%=n%>_rec(t, i, v, <%=n/2%>);
}

int set_array2d<%=n%>_rec_j;

P set_array2d<%=n%>_rec(P t, int i, P v, int n) {
  if (n == 0) {
    t = set_array<%=n%>(t, set_array2d<%=n%>_rec_j, v);
  } else {
    if (i < n) {
      t = P(set_array2d<%=n%>_rec(fst(t), i, v, n / 2), snd(t));
    } else {
      t = P(fst(t), set_array2d<%=n%>_rec(snd(t), i - n, v, n / 2));
    }
  }
  return t;
}

P set_array2d<%=n%>(P t, int i, int j, P v) {
  set_array2d<%=n%>_rec_j = j;
  return set_array2d<%=n%>_rec(t, i, v, <%= n/2 %>);
}

#endif  // SBL_SBL_H_
