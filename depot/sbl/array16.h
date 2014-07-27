#ifndef SBL_ARRAY16_H_
#define SBL_ARRAY16_H_

#include "translator/lib.h"

P create_array16();
P list_to_array16(P list);
P get_array16(P t, int i);
P set_array16(P t, int i, P v);

P create_array2d16();
P list2d_to_array2d16(P list);
P get_array2d16(P t, int i, int j);
P set_array2d16(P t, int i, int j, P v);

#endif  // SBL_ARRAY16_H_
