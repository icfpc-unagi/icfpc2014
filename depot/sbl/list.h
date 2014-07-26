#ifndef SBL_LIST_H_
#define SBL_LIST_H_

#include "translator/lib.h"

P read_list(P list, int n);
P write_list(P list, int n, P val);
P read_list2d(P list, int i, int j);
P write_list2d(P list, int i, int j, P val);
int length_list(P list);
P reverse_list(P list);
P replicate_list(int n, P val);
P split_list(P xs, int n);

#endif  // SBL_TREE_H_
