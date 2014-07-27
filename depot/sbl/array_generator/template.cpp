#ifndef SBL_SBL_H_

#include "sbl/array<%=n%>.h"

P list_to_array<%=n%>_rec(P t, int size) {
  P tmp;
  if (atom(t)) {
    t = P(0, 0);
  } else {
    if (size > 1) {
      t = list_to_array<%=n%>_rec(t, size / 2);
      tmp = list_to_array<%=n%>_rec(snd(t), size / 2);
      t = P(P(fst(t), fst(tmp)), snd(tmp));
    }
  }
  return t;
}

P list_to_array<%=n%>(P list) {
  return fst(list_to_array<%=n%>_rec(list, <%=n%>));
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

P create_array_rec(int n) {
  if (n == 1) {
    return top(0);
  } else {
    return P(create_array_rec(n / 2), create_array_rec(n / 2));
  }
}

P create_array<%=n%>() {
  return create_array_rec(<%=n%>);
}

#endif  // SBL_SBL_H_
