#include "tree.b"


P debug_tree(){
  P list;
  P tree;
  P gomi;
  list = P(3, P(1, P(4, P(1, P(5, P(9, 0))))));
  gomi = debug(list);
  tree = list_to_tree(list);
  gomi = debug(tree);
  gomi = debug(read_tree(tree,0));
  gomi = debug(read_tree(tree,1));
  gomi = debug(read_tree(tree,2));
  gomi = debug(read_tree(tree,3));
  gomi = debug(read_tree(tree,4));
  gomi = debug(read_tree(tree,5));
  tree = write_tree(tree,3,100);
  gomi = debug(tree);
  return 0;
}

P run() {
  P gomi;
  gomi = debug_tree();
  return gomi;
}

P step(P state, P game) {
  return P(state, 3);
}
P init(P game, P nazo) {
  P gomi;
  gomi = run();
  return P(0, 0);
}
