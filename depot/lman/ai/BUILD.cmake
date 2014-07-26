cc_library(
    NAME "chokudai-10"
    SOURCES "chokudai-10.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-4"
    SOURCES "chokudai-4.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-8"
    SOURCES "chokudai-8.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "rounding"
    SOURCES "rounding.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "ai"
    SOURCES "ai.cc"
    DEPENDENCIES
        ":chokudai-10"
        ":chokudai-4"
        ":chokudai-8"
        ":rounding"
)
