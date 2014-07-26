#include "translator/lib.h"
#include "sbl/tree.cpp"


void debug_tree(){
  P list;
  P tree;
  list = P(3, P(1, P(4, P(1, P(5, P(9, 0))))));
  debug(list);
  tree = list_to_tree(list);
  debug(tree);
  debug(read_tree(tree,0));
  debug(read_tree(tree,1));
  debug(read_tree(tree,2));
  debug(read_tree(tree,3));
  debug(read_tree(tree,4));
  debug(read_tree(tree,5));
  tree = write_tree(tree,3,100);
  debug(tree);
}
void debug_tree2d(){
  P list;
  P tree;
  list =
    P(P(3, P(1, P(4, P(1, P(5, P(9, 0)))))),
    P(P(5, P(3, P(5, P(8, P(9, P(7, 0)))))),
    P(P(2, P(3, P(8, P(4, P(6, P(2, 0)))))),
    0)));
  tree = list2d_to_tree2d(list2d);
  debug(tree);
  tree = write_tree2d(tree);
}

void run() {
  debug_tree();
  debug_tree2d();
}
