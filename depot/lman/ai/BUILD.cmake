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
    NAME "ai"
    SOURCES "ai.cc"
    DEPENDENCIES
        ":chokudai-10"
)
