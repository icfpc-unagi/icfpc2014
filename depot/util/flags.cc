#include "util/flags.h"

#include <gflags/gflags.h>

DEFINE_int32(print_for_test, 0, "Print information for testing.");
DEFINE_bool(silent, false, "Suppress status messages.");
DEFINE_bool(print_stats, true, "Print game stats.");
DEFINE_string(ghosts, "fickle", "Comma-separated list of ghosts to use.");
DEFINE_bool(print_color, true, "Prettify the field state");
