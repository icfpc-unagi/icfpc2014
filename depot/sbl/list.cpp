// vi:filetype=cpp:

// P read_list(P list, int n)
// P write_list(P list, int n, P value)
//
// list2d
// P read_list2d(P list, int i, int j)
// P write_list2d(P list, int i, int j, P value) {
//
// int length_list(P list)
// P reverse_list(P list)
#pragma once

P read_list(P list, int n) {
  P res;
  if (n == 0) {
    res = fst(list);
  } else {
    res = read_list(list, n-1);
  }
  return res;
}

P write_list(P list, int n, P val) {
  P res;
  if (n == 0) {
    res = P(val, snd(list));
  } else {
    res = P(
	fst(list),
	write_list(snd(list), n-1, val) );
  }
  return res;
}

// read list[i][j]
P read_list2d(P list, int i, int j) {
  return read_list(read_list(list, i), j);
}

// write list[i][j]
P write_list2d(P list, int i, int j, P val) {
  return write_list(list, i, write_list(read_list(list,i), j, val) );
}

int length_list(P list) {
  int res;
  if (atom(list)) {
    res = 0;
  } else {
    res = 1 + length_list(snd(list));
  }
  return res;
}


P reverse_list1(P list, P tmp) {
  P res;
  if (atom(list)) {
    res = tmp;
  } else {
    res = reverse_list1(snd(list), P(fst(list), tmp));
  }
  return res;
}
P reverse_list(P list) {
  return reverse_list1(list, top(0));
}


P replicate_list(int n, P val) {
  P res;
  res = top(0);
  while (n > 0) {
    res = P(val, res);
    n = n-1;
  }
  return res;
}
