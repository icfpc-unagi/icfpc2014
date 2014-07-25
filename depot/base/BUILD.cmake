cc_library(
    NAME "macro"
    SOURCES "macro.cc"
)

cc_library(
    NAME "base"
    SOURCES "base.cc"
    DEPENDENCIES
        "#glog"
        "#gflags"
)

cc_library(
    NAME "string-printf"
    SOURCES "string-printf.cc"
)
