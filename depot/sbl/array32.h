#ifndef SBL_ARRAY32_H_
#define SBL_ARRAY32_H_

#include "translator/lib.h"

P create_array32();
P list_to_array32(P list);
P get_array32(P t, int i);
P set_array32(P t, int i, P v);

P create_array2d32();
P list2d_to_array2d32(P list);
P get_array2d32(P t, int i, int j);
P set_array2d32(P t, int i, int j, P v);

#endif  // SBL_ARRAY32_H_
