cc_library(
    NAME "chokudai-10"
    SOURCES "chokudai-10.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-12"
    SOURCES "chokudai-12.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-13"
    SOURCES "chokudai-13.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-14"
    SOURCES "chokudai-14.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-4"
    SOURCES "chokudai-4.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "chokudai-8"
    SOURCES "chokudai-8.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "migi"
    SOURCES "migi.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "orz"
    SOURCES "orz.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "piyo"
    SOURCES "piyo.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "rounding"
    SOURCES "rounding.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "tos-hungry"
    SOURCES "tos-hungry.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "tos-sokushi-kaihi"
    SOURCES "tos-sokushi-kaihi.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "tos-yowaki"
    SOURCES "tos-yowaki.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "wata-10"
    SOURCES "wata-10.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "wata_cpp"
    SOURCES "wata_cpp.cc"
    DEPENDENCIES
        "//base"
        "//lman:lambda-man"
        "//sbl"
        "//translator:lib"
)

cc_library(
    NAME "ai"
    SOURCES "ai.cc"
    DEPENDENCIES
        ":chokudai-10"
        ":chokudai-12"
        ":chokudai-13"
        ":chokudai-14"
        ":chokudai-4"
        ":chokudai-8"
        ":migi"
        ":orz"
        ":piyo"
        ":rounding"
        ":tos-hungry"
        ":tos-sokushi-kaihi"
        ":tos-yowaki"
        ":wata-10"
        ":wata_cpp"
)
