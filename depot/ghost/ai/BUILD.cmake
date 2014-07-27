cc_library(
    NAME "chokudai"
    SOURCES "chokudai.cc"
    DEPENDENCIES
        "//base"
        "//ghost"
)

cc_library(
    NAME "fickle"
    SOURCES "fickle.cc"
    DEPENDENCIES
        "//base"
        "//ghost"
)

cc_library(
    NAME "fickle_debug"
    SOURCES "fickle_debug.cc"
    DEPENDENCIES
        "//base"
        "//ghost"
)

cc_library(
    NAME "sakichokudai"
    SOURCES "sakichokudai.cc"
    DEPENDENCIES
        "//base"
        "//ghost"
)

cc_library(
    NAME "ai"
    SOURCES "ai.cc"
    DEPENDENCIES
        ":chokudai"
        ":fickle"
        ":fickle_debug"
        ":sakichokudai"
)
