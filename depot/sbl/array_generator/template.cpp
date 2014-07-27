#ifndef SBL_SBL_H_

#include "sbl/array<%=n%>.h"

P create_array<%=n%>_rec(int n) {
  P a;
  if (n == 1) {
    a = top(0);
  } else {
    a = P(create_array<%=n%>_rec(n / 2), create_array<%=n%>_rec(n / 2));
  }
  return a;
}

P create_array<%=n%>() {
  return create_array<%=n%>_rec(<%=n%>);
}

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

P create_array2d<%=n%>_rec(int n) {
  P t;
  if (n == 1) {
    t = create_array<%=n%>();
  } else {
    t = P(create_array2d<%=n%>_rec(n / 2), create_array2d<%=n%>_rec(n / 2));
  }
  return t;
}

P create_array2d<%=n%>() {
  return create_array2d<%=n%>_rec(<%=n%>);
}

P list2d_to_array2d<%=n%>_rec(P l) {
  P t;
  if (atom(l)) {
    t = top(0);
  } else {
    t = P(list_to_array<%=n%>(fst(l)), list2d_to_array2d<%=n%>_rec(snd(l)));
  }
  return t;
}

P list2d_to_array2d<%=n%>(P l) {
  return list_to_array<%=n%>(list2d_to_array2d<%=n%>_rec(l));
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

P get_array2d<%=n%>(P t, int i, int j) {
  return get_array<%=n%>(get_array<%=n%>(t, i), j);
}

#endif  // SBL_SBL_H_
