#include "translator/lib.h"
#include "tree.b"


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

void run() {
  debug_tree();
}
