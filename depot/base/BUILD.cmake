cc_library(
    NAME "macro"
    SOURCES "macro.cc"
)

cc_library(
    NAME "base"
    SOURCES "base.cc"
    DEPENDENCIES
        ":split"
        ":string-printf"
        "#glog"
        "#gflags"
)

cc_library(
    NAME "split"
    SOURCES "split.cc"
)

cc_test(
    NAME "split_test"
    SOURCES "split_test.cc"
    DEPENDENCIES
        ":split"
        "//gtest:gtest_main"
)

cc_library(
    NAME "string-printf"
    SOURCES "string-printf.cc"
)
