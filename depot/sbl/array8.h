#ifndef SBL_ARRAY8_H_
#define SBL_ARRAY8_H_

#include "translator/lib.h"

P create_array8();
P list_to_array8(P list);
P get_array8(P t, int i);
P set_array8(P t, int i, P v);

P create_array2d8();
P list2d_to_array2d8(P list);
P get_array2d8(P t, int i, int j);
P set_array2d8(P t, int i, int j, P v);

#endif  // SBL_ARRAY8_H_
