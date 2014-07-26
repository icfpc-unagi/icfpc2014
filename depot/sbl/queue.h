#ifndef SBL_QUEUE_H_
#define SBL_QUEUE_H_

#include "translator/lib.h"

P create_queue();
int is_empty_queue(P queue);
P push_queue(P queue, P x);
P front_queue(P queue);
P pop_queue(P queue);

#endif  // SBL_QUEUE_H_
