#ifndef SBL_STACK_H_
#define SBL_STACK_H_

#include "translator/lib.h"

P create_stack();
int is_empty_stack(P stack);
P push_stack(P stack, P x);
P top_stack(P stack);
P pop_stack(P stack);

#endif  // SBL_STACK_H_
