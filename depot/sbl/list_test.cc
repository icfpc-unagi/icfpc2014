#include "translator/lib.h"
#include "list.b"



void debug_list(){
  P list;
  list = P(3, P(1, P(4, P(1, P(5, P(9, 0))))));
  debug(list);
  debug(length(list));
  list = reverse_list(list);
  debug(list);
  return;
}

void run() {
  debug_list();
  return;
}
