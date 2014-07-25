cc_library(
    NAME "hello-world"
    SOURCES "hello-world.cc"
    DEPENDENCIES
        "//base"
)

cc_test(
    NAME "hello-world_test"
    SOURCES "hello-world_test.cc"
    DEPENDENCIES
        ":hello-world"
        "//gtest:gtest_main"
)

cc_binary(
    NAME "hello-world-main"
    SOURCES "hello-world-main.cc"
    DEPENDENCIES
        ":hello-world"
)
