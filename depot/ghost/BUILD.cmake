cc_library(
    NAME "ghost"
    SOURCES "ghost.cc"
    DEPENDENCIES
        "//base"
        "//base:string-printf"
        "//sim"
)

cc_library(
    NAME "ghost-ai-manager"
    SOURCES "ghost-ai-manager.cc"
    DEPENDENCIES
        "//sim"
)
