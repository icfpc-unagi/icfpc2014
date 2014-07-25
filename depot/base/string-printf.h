#ifndef BASE_STRING_PRINTF_H_
#define BASE_STRING_PRINTF_H_

#include <string>

void SStringPrintf(string* output, const char* format, ...);
void StringAppendF(string* output, const char* format, ...);
string StringPrintf(const char* format, ...);

#endif  // BASE_STRING_PRINTF_H_
