#include "translator/lib.h"
#include "sbl/list.h"



void debug_list(){
  P list;
  list = P(3, P(1, P(4, P(1, P(5, P(9, 0))))));
  debug(list);
  debug(length_list(list));
  list = reverse_list(list);
  debug(list);
  debug(replicate_list(3,-1));
}

void run() {
  debug_list();
}
