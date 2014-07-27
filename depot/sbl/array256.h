#ifndef SBL_ARRAY256_H_
#define SBL_ARRAY256_H_

#include "translator/lib.h"

P create_array256();
P list_to_array256(P list);
P get_array256(P t, int i);
P set_array256(P t, int i, P v);

P create_array2d256();
P list2d_to_array2d256(P list);
P get_array2d256(P t, int i, int j);
P set_array2d256(P t, int i, int j, P v);

#endif  // SBL_ARRAY256_H_
