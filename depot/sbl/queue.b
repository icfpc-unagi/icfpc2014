// vi:filetype=cpp:

#include "stack.b"
#include "list.b"

P create_queue() {
  return P(create_stack(), create_stack());
}

int is_empty_queue(P queue) {
  return is_empty_stack(fst(queue));
}

P push_queue(P queue, P x) {
  P q;
  if (is_empty_stack(fst(queue))) {
    q = create_stack();
    q = push_stack(q, x);
    q = P(q, create_stack());
  } else {
    q = P(fst(queue), push_stack(snd(queue), x));
  }
  return q;
}

P front_queue(P queue) {
  return top_stack(fst(queue));
}

P pop_queue(P queue) {
  P x;
  P q;
  x = top_stack(fst(queue));
  q = pop_stack(fst(queue));
  if (is_empty_stack(q)) {
    q = P(reverse_list(snd(queue)), create_stack());
  } else {
    q = P(q, snd(queue));
  }
  return q;
}
