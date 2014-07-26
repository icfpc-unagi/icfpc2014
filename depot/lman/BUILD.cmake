cc_library(
    NAME "chokudai-ai-ver4"
    SOURCES "lman.cc"
    DEPENDENCIES
        "//base"
        "//translator/ai:libchokudai-ai-ver4"
)
