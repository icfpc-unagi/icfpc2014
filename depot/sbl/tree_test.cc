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
  return;
}

void run() {
  debug_tree();
  return;
}

P step(P state, P game) {
  return P(state, 3);
}
P init(P game, P nazo) {
  run();
  return P(0, 0);
}
