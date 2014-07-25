#ifndef BASE_MACRO_H_
#define BASE_MACRO_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif  // BASE_MACRO_H_
