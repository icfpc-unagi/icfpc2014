#include "translator/lib.h"
#include "sbl/tree.cpp"


void debug_tree(){
  P list;
  P tree;
  list = P(3, P(1, P(4, P(1, 0))));
  debug(list);
  tree = list_to_tree(list);

  debug(tree);
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
  tree = list2d_to_tree2d(list);
  debug(tree);
  tree = write_tree2d(tree,1,4,12345);
  debug(tree);
  debug(read_tree2d(tree,0,0));
  debug(read_tree2d(tree,0,1));
  debug(read_tree2d(tree,0,2));
  debug(read_tree2d(tree,0,3));
  debug(read_tree2d(tree,0,4));
  debug(read_tree2d(tree,0,5));
  debug(read_tree2d(tree,1,0));
  debug(read_tree2d(tree,1,1));
  debug(read_tree2d(tree,1,2));
  debug(read_tree2d(tree,1,3));
  debug(read_tree2d(tree,1,4));
  debug(read_tree2d(tree,1,5));
  debug(read_tree2d(tree,2,0));
  debug(read_tree2d(tree,2,1));
  debug(read_tree2d(tree,2,2));
  debug(read_tree2d(tree,2,3));
  debug(read_tree2d(tree,2,4));
  debug(read_tree2d(tree,2,5));
}

void run() {
  debug_tree();
  debug_tree2d();
}
