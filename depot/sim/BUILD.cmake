cc_library(
    NAME "game-interface"
    SOURCES "game-interface.cc"
    DEPENDENCIES
        "//base"
        "//util:coordinate"
)

cc_library(
    NAME "sim"
    SOURCES "sim.cc"
    DEPENDENCIES
        ":game-interface"
        "//base"
        "//util:coordinate"
)

cc_test(
    NAME "sim_test"
    SOURCES "sim_test.cc"
    DEPENDENCIES
        ":sim"
        "//gtest:gtest_main"
)

cc_binary(
    NAME "sim_main"
    SOURCES "sim_main.cc"
    DEPENDENCIES
        ":sim"
        "//ghost/ai:fickle"
)
