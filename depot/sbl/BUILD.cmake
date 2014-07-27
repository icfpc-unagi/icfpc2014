cc_library(
    NAME "sbl"
    SOURCES "sbl.cc"
    DEPENDENCIES
        ":tree"
        ":list"
        ":stack"
        ":queue"
        ":array"
)

cc_library(
    NAME "array"
    SOURCES "array256.cpp" "array256_translator.cpp" "array128.cpp" "array128_translator.cpp" "array64.cpp" "array64_translator.cpp" "array32.cpp" "array32_translator.cpp" "array16.cpp" "array16_translator.cpp"
    DEPENDENCIES
        "//translator:lib"
	":list"
)

cc_library(
    NAME "tree"
    SOURCES "tree.cpp"
    DEPENDENCIES
        "//translator:lib"
	":list"
)

cc_library(
    NAME "fasttree"
    SOURCES "fasttree.cpp"
    DEPENDENCIES
        "//translator:lib"
	":list"
)

cc_library(
    NAME "list"
    SOURCES "list.cpp"
    DEPENDENCIES
        "//translator:lib"
)

cc_library(
    NAME "stack"
    SOURCES "stack.cpp"
    DEPENDENCIES
        "//translator:lib"
)

cc_library(
    NAME "queue"
    SOURCES "queue.cpp"
    DEPENDENCIES
        "//translator:lib"
	":list"
	":stack"
)
