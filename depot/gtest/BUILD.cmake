cc_library(
    NAME "gtest"
    SOURCES "gtest.cc"
    DEPENDENCIES
        "#gtest"
        "#pthread"
)

cc_library(
    NAME "gtest_main"
    SOURCES "gtest_main.cc"
    DEPENDENCIES
        "#gtest"
        "#glog"
        "#gflags"
        "#pthread"
)
