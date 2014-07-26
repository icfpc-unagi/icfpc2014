#include "translator/lib.h"
#include "queue.b"

void test(){
  P q;
  q = create_queue();
  q = push_queue(q, top(100));

  q = push_queue(q, top(200));
  q = push_queue(q, top(300));
  q = push_queue(q, top(400));
  debug(q);
  debug(front_queue(q));
  q = pop_queue(q);
  debug(q);

  q = push_queue(q, top(500));
  q = push_queue(q, top(600));
  q = push_queue(q, top(700));

  while (is_empty_queue(q) == 0) {
    debug(front_queue(q));
    q = pop_queue(q);
    debug(q);
  }
}

void run() {
  test();
}

