#ifndef SBL_ARRAY128_H_
#define SBL_ARRAY128_H_

#include "translator/lib.h"

P create_array128();
P list_to_array128(P list);
P get_array128(P t, int i);
P set_array128(P t, int i, P v);

P create_array2d128();
P list2d_to_array2d128(P list);
P get_array2d128(P t, int i, int j);
P set_array2d128(P t, int i, int j, P v);

#endif  // SBL_ARRAY128_H_
