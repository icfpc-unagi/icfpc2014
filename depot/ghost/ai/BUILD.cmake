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
    NAME "ai"
    SOURCES "ai.cc"
    DEPENDENCIES
        ":chokudai"
        ":fickle"
        "//ghost:ghost-ai-manager"
)
