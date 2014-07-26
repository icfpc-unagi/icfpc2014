cc_binary(
    NAME "fickle-main"
    SOURCES "fickle-main.cc"
    DEPENDENCIES
        ":fickle"
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
