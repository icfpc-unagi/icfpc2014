#include "translator/lib.h"
#include "sbl/list.h"



void debug_list(){
  P list;
  list = P(3, P(1, P(4, P(1, P(5, P(9, 0))))));
  debug(list);
  debug(read_list(list,0));
  debug(read_list(list,1));
  debug(read_list(list,2));
  debug(read_list(list,3));
  debug(read_list(list,4));
  debug(read_list(list,5));
  list = reverse_list(list);
  debug(list);
  debug(length_list(list));
  debug(replicate_list(3,-1));
}

void run() {
  debug_list();
}
