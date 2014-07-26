#ifndef SBL_TREE_H_
#define SBL_TREE_H_

P read_tree2(int n, int k, P tr);
P read_tree1(int n, int k, P tr);
P read_tree(P tr, int n);
P write_tree2(int n, int k, P v, P tr);
P write_tree1(int n, int k, P v, P tr);
P write_tree(P tr, int n, P v);
P gp2(P ts);
P l2t2(int k, P ts);
P split_list(P xs, int n);
P l2t1(int k, P xs);
P list_to_tree(P xs);
P read_tree2d(P tree, int i, int j);
P write_tree2d(P tree, int i, int j, P val);
P list2d_to_tree2d_sub(P xss);
P list2d_to_tree2d(P xss);

#endif  // SBL_TREE_H_
