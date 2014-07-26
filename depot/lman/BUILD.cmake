cc_library(
    NAME "lambda-man"
    SOURCES "lambda-man.cc"
    DEPENDENCIES
        "//base"
        "//sim:lambda-man-interface"
)

cc_library(
    NAME "lambda-man-ai-manager"
    SOURCES "lambda-man-ai-manager.cc"
    DEPENDENCIES
        "//lman/ai"
        "//sim:lambda-man-interface"
)
