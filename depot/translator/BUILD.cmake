cc_library(
    NAME "lib"
    SOURCES "lib.cc"
    DEPENDENCIES
        "//base"
)

cc_library(
    NAME "main"
    SOURCES "main.cc"
    DEPENDENCIES
        "//base"
)
