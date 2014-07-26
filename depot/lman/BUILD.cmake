cc_library(
    NAME "lambda-man"
    SOURCES "lambda-man.cc"
    DEPENDENCIES
        "//base"
        "//sim"
)

cc_library(
    NAME "lman"
    SOURCES "lman.cc"
    DEPENDENCIES
        "//base"
)
