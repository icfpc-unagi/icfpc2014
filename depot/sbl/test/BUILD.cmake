cc_binary (
  NAME "array256_test"
    SOURCES "array256_test.cpp"
            "../../translator/main_run.cc"
    DEPENDENCIES
        "//base"
        "//translator:lib"
	"//sbl:array256"
)

cc_binary (
    NAME "list_test"
    SOURCES "list_test.cpp"
            "../../translator/main_run.cc"
    DEPENDENCIES
        "//base"
        "//translator:lib"
	"//sbl:list"
)

cc_binary (
    NAME "tree_test"
    SOURCES "tree_test.cpp"
            "../../translator/main_run.cc"
    DEPENDENCIES
        "//base"
        "//translator:lib"
	"//sbl:tree"
)

cc_binary (
    NAME "fasttree_test"
    SOURCES "fasttree_test.cpp"
            "../../translator/main_run.cc"
    DEPENDENCIES
        "//base"
        "//translator:lib"
	"//sbl:fasttree"
)

cc_binary (
    NAME "queue_test"
    SOURCES "queue_test.cpp"
            "../../translator/main_run.cc"
    DEPENDENCIES
        "//base"
        "//translator:lib"
	"//sbl:queue"
)

cc_binary (
    NAME "stack_test"
    SOURCES "stack_test.cpp"
            "../../translator/main_run.cc"
    DEPENDENCIES
        "//base"
        "//translator:lib"
	"//sbl:stack"
)


# file(GLOB test_sources "${PACKAGE_DIRECTORY}/*.cpp")
#
# foreach(test_source ${test_sources})
#   string(REGEX REPLACE "^.*/" "" test_source "${test_source}")
#   string(REGEX REPLACE "\\.[^.]+$" "" test_target "${test_source}")
#
#   cc_library(
#       NAME "lib${test_target}"
#       SOURCES "${test_source}"
#       DEPENDENCIES
#           "//base"
#           "//translator:lib"
#   )
#
#   cc_binary(
#       NAME "${test_target}"
#       SOURCES "../../translator/main_run.cc"
#       DEPENDENCIES
#           ":lib${test_target}"
#   )
# endforeach()
