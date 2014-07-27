#ifndef SBL_ARRAY<%=n%>_H_
#define SBL_ARRAY<%=n%>_H_

#include "translator/lib.h"

P list_to_array<%=n%>(P list);
P create_array<%=n%>();
P get_array<%=n%>(P t, int i);
P set_array<%=n%>(P t, int i, P v);

P create_array2d<%=n%>();
P get_array2d<%=n%>(P t, int i, int j);
P set_array2d<%=n%>(P t, int i, int j, P v);

#endif  // SBL_ARRAY<%=n%>_H_
