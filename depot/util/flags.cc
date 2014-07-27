#include "util/flags.h"

#include <gflags/gflags.h>

DEFINE_int32(print_for_test, 0, "Print information for testing.");
DEFINE_bool(silent, false, "Suppress status messages.");
