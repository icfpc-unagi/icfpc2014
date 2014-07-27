cc_library(
    NAME "ghost"
    SOURCES "ghost.cc"
    DEPENDENCIES
        "//base"
        "//base:string-printf"
        "//sim:ghost-interface"
        "//util:flags"
)

cc_library(
    NAME "ghost-ai-manager"
    SOURCES "ghost-ai-manager.cc"
    DEPENDENCIES
        "//ghost/ai"
        "//sim:ghost-interface"
        "//util:flags"
)

cc_binary(
    NAME "ghost-ai-main"
    SOURCES "ghost-ai-main.cc"
    DEPENDENCIES
        "//ghost/ai"
        "//ghost:ghost-ai-manager"
)
