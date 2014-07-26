#include "translator/lib.h"
#include "stack.b"

void test() {
  P s;
  s = create_stack();
  s = push_stack(s, top(1));
  s = push_stack(s, top(2));
  s = push_stack(s, top(3));
  s = push_stack(s, top(4));

  while (is_empty_stack(s) == 0) {
    debug(top_stack(s));
    s = pop_stack(s);
  }
}

void run() {
  test();
}
