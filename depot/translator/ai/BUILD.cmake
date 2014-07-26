# file(GLOB ai_sources "${PACKAGE_DIRECTORY}/*.cc")
# 
# foreach(ai_source ${ai_sources})
#   string(REGEX REPLACE "^.*/" "" ai_source "${ai_source}")
#   string(REGEX REPLACE "\\.[^.]+$" "" ai_target "${ai_source}")
# 
#   cc_library(
#       NAME "lib${ai_target}"
#       SOURCES "${ai_source}"
#       DEPENDENCIES
#           "//base"
#           "//translator:lib"
#   )
# 
#   cc_binary(
#       NAME "${ai_target}"
#       SOURCES "../main.cc"
#       DEPENDENCIES
#           ":lib${ai_target}"
#   )
# 
#   cc_binary(
#       NAME "simulate_${ai_target}"
#       SOURCES "../dummy.cc"
#       DEPENDENCIES
#           ":lib${ai_target}"
#           "//sim:libsim_main"
#   )
# endforeach()
