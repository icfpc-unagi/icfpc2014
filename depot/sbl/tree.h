#ifndef SBL_TREE_H_
#define SBL_TREE_H_

#include "translator/lib.h"

P read_tree(P tr, int n);
P write_tree(P tr, int n, P v);
P list_to_tree(P xs);
P read_tree2d(P tree, int i, int j);
P write_tree2d(P tree, int i, int j, P val);
P list2d_to_tree2d(P xss);

#endif  // SBL_TREE_H_
