cc_library(
    NAME "sbl"
    SOURCES "sbl.cc"
    DEPENDENCIES
        ":tree"
)

cc_library(
    NAME "tree"
    SOURCES "tree.cpp"
    DEPENDENCIES
        "//translator:lib"
)
