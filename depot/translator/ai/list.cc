#include "list.b"


P debug_list(){
  P list;
  P gomi;
  list = P(3, P(1, P(4, P(1, P(5, P(9, 0))))));
  gomi = debug(list);
  gomi = debug(length(list));
  list = reverse_list(list);
  gomi = debug(list);
  return 0;
}

P run() {
  P gomi;
  gomi = debug_list();
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
