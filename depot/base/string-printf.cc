#include <stdarg.h>
#include <string>

#include "base/string-printf.h"

namespace {

void InternalStringPrintf(string* output, const char* format, va_list ap) {
  char space[128];    // try a small buffer and hope it fits

  // It's possible for methods that use a va_list to invalidate
  // the data in it upon use.  The fix is to make a copy
  // of the structure before using it and use that copy instead.
  va_list backup_ap;
  va_copy(backup_ap, ap);
  int bytes_written = vsnprintf(space, sizeof(space), format, backup_ap);
  va_end(backup_ap);

  if ((bytes_written >= 0) && (bytes_written < sizeof(space))) {
    output->append(space, bytes_written);
    return;
  }

  // Repeatedly increase buffer size until it fits.
  int length = sizeof(space);
  while (true) {
    if (bytes_written < 0) {
      // Older snprintf() behavior. :-(  Just try doubling the buffer size
      length *= 2;
    } else {
      // We need exactly "bytes_written+1" characters
      length = bytes_written+1;
    }
    char* buf = new char[length];

    // Restore the va_list before we use it again
    va_copy(backup_ap, ap);
    bytes_written = vsnprintf(buf, length, format, backup_ap);
    va_end(backup_ap);

    if ((bytes_written >= 0) && (bytes_written < length)) {
      output->append(buf, bytes_written);
      delete[] buf;
      return;
    }
    delete[] buf;
  }
}

}  // namespace

// Clears output before writing to it.
void SStringPrintf(string* output, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  output->clear();
  InternalStringPrintf(output, format, ap);
  va_end(ap);
}

void StringAppendF(string* output, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  InternalStringPrintf(output, format, ap);
  va_end(ap);
}

string StringPrintf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  string output;
  InternalStringPrintf(&output, format, ap);
  va_end(ap);
  return output;
}
