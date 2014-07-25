cc_library(
    NAME "ghost"
    SOURCES "ghost.cc"
    DEPENDENCIES
        "//base"
        "//base:string-printf"
        "//sim"
)

# cc_test(
#     NAME "hello-world_test"
#     SOURCES "hello-world_test.cc"
#     DEPENDENCIES
#         ":hello-world"
#         "//gtest:gtest_main"
# )
# 
# cc_binary(
#     NAME "hello-world-main"
#     SOURCES "hello-world-main.cc"
#     DEPENDENCIES
#         ":hello-world"
# )
# 