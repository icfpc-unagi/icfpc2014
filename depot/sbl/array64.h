#ifndef SBL_ARRAY64_H_
#define SBL_ARRAY64_H_

#include "translator/lib.h"

P create_array64();
P list_to_array64(P list);
P get_array64(P t, int i);
P set_array64(P t, int i, P v);

P create_array2d64();
P list2d_to_array2d64(P list);
P get_array2d64(P t, int i, int j);
P set_array2d64(P t, int i, int j, P v);

#endif  // SBL_ARRAY64_H_
