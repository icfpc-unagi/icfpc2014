cc_library(
    NAME "character"
    SOURCES "character.cc"
    DEPENDENCIES
        ":game-interface"
        "//base"
        "//util:coordinate"
)

cc_library(
    NAME "game-interface"
    SOURCES "game-interface.cc"
    DEPENDENCIES
        "//base"
        "//util:coordinate"
)

cc_library(
    NAME "ghost-interface"
    SOURCES "ghost-interface.cc"
    DEPENDENCIES
        ":game-interface"
        ":character"
        "//base"
        "//util:coordinate"
)

cc_library(
    NAME "lambda-man-interface"
    SOURCES "lambda-man-interface.cc"
    DEPENDENCIES
        ":game-interface"
        ":character"
        "//base"
        "//util:coordinate"
)

cc_library(
    NAME "sim"
    SOURCES "sim.cc"
    DEPENDENCIES
        ":character"
        ":game-interface"
        "//base"
        "//ghost:ghost-ai-manager"
        "//lman:lambda-man-ai-manager"
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

cc_library(
    NAME "libsim_main"
    SOURCES "sim_main.cc"
    DEPENDENCIES
        ":sim"
        "//ghost/ai:fickle"
)
