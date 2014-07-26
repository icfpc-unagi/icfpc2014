# Flame - Easy syntax build system.
#
# A build system whose syntax is like Twitter's Pants and Google's Blaze:
#   Pants (Twitter) - http://pantsbuild.github.io/,
#   Blaze (Google) - http://goo.gl/3ppAAC.

cmake_minimum_required(VERSION 2.8.12)
project(flame)

# Basic settings.
enable_testing()
include(CMakeParseArguments)

################################################################################
# Flame Settings
################################################################################

# Set FLAME_ROOT.
set(FLAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
string(REGEX REPLACE "/+$" "" FLAME_ROOT "${FLAME_ROOT}")
include_directories("${FLAME_ROOT}/depot")
message(STATUS "Flame root directory: ${FLAME_ROOT}")

# Set FLAME_LIBRARY_ROOT
set(FLAME_BINARY_ROOT "${CMAKE_CURRENT_BINARY_DIR}/flame-binary")
set(FLAME_LIBRARY_ROOT "${CMAKE_CURRENT_BINARY_DIR}/flame-library")
message(STATUS "Flame library root directory: ${FLAME_LIBRARY_ROOT}")
set(FLAME_LIBRARY_BINARY_ROOT
    "${CMAKE_CURRENT_BINARY_DIR}/flame-library-binary")
message(
    STATUS "Flame library binary root directory: ${FLAME_LIBRARY_BINARY_ROOT}")
exec_program(mkdir ARGS -p "${FLAME_LIBRARY_ROOT}")
exec_program(mkdir ARGS -p "${FLAME_LIBRARY_BINARY_ROOT}/include")
exec_program(mkdir ARGS -p "${FLAME_LIBRARY_BINARY_ROOT}/lib")
include_directories(${FLAME_LIBRARY_BINARY_ROOT}/include)
include_directories(${FLAME_BINARY_ROOT}/depot)
link_directories(${FLAME_LIBRARY_BINARY_ROOT}/lib)

add_compile_options(-std=c++0x)
add_compile_options(--include=base/stl.h)

if("${CMAKE_BUILD_TYPE}" STREQUAL "asan")
  add_compile_options(-g)
  add_compile_options(-fsanitize-memory-track-origins)
  add_compile_options(-fno-omit-frame-pointer)
  add_compile_options(-gline-tables-only)
  add_compile_options(-fsanitize=address)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "msan")
  add_compile_options(-g)
  add_compile_options(-fsanitize-memory-track-origins)
  add_compile_options(-fno-omit-frame-pointer)
  add_compile_options(-gline-tables-only)
  add_compile_options(-fsanitize=memory)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "usan")
  add_compile_options(-g)
  add_compile_options(-fsanitize-memory-track-origins)
  add_compile_options(-fno-omit-frame-pointer)
  add_compile_options(-gline-tables-only)
  add_compile_options(-fsanitize=undefined)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_compile_options(-g)
else()
  add_compile_options(-O2)
endif()

if("${CMAKE_SYSTEM}" MATCHES Darwin)
  set(CMAKE_CXX_LINK_FLAGS "-Wl,-all_load")
elseif("${CMAKE_SYSTEM}" MATCHES IRIX)
  set(CMAKE_CXX_LINK_FLAGS "-Wl,-all")
else()
  set(CMAKE_CXX_LINK_FLAGS "-Wl,-whole-archive -Wl,-allow-multiple-definition")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -static-libgcc")
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -static-libstdc++")
  # For Ubuntu 12.04
  set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -lpthread")
endif()

################################################################################
# Target Functions
################################################################################

function(cc_library)
  # Parse function arguments.
  set(novalue_options BINARY TEST)
  set(onevalue_options NAME)
  set(multivalue_options SOURCES HEADERS DEPENDENCIES)
  cmake_parse_arguments(
      TARGET
      "${novalue_options}" "${onevalue_options}" "${multivalue_options}"
      "${ARGN}"
  )

  # Prepare a target path.
  set(TARGET_PATH "${PACKAGE_DIRECTORY}/${TARGET_NAME}.cc_library")
  message("  target: ${TARGET_PATH}")
  flatten_path("${TARGET_PATH}" TARGET_PATH)

  add_dependencies("${mkdir_target}__all" ${TARGET_PATH})

  # Prepare source lists.
  set(sources)
  foreach(source ${TARGET_SOURCES} ${TARGET_HEADERS})
    list(APPEND sources "${PACKAGE_DIRECTORY}/${source}")
  endforeach()
  add_library("${TARGET_PATH}" STATIC ${sources})
  set_target_properties("${TARGET_PATH}" PROPERTIES LINKER_LANGUAGE CXX)

  # Prepare dependencies.
  parse_dependencies(${TARGET_DEPENDENCIES})
  # Link external dependencies.  They are specified using "#" in the
  # DEPENDENCIES field.
  if(NOT "${LIBRARY_DEPENDENCIES}" STREQUAL "")
    target_link_libraries("${TARGET_PATH}" ${LIBRARY_DEPENDENCIES})
  endif()
  # Treat all dependencies as cc_library.
  if(NOT "${DEPENDENCIES}" STREQUAL "")
    foreach(dependency ${DEPENDENCIES})
      flatten_path("${dependency}.cc_library" dependency)
      target_link_libraries("${TARGET_PATH}" "${dependency}")
    endforeach()
  endif()

  # Prepare binary-specific things.
  if("${TARGET_BINARY}")
    set(BINARY_TARGET "flame-binary/${PACKAGE_DIRECTORY}/${TARGET_NAME}")
    message("  target: ${BINARY_TARGET}")
    add_executable("${BINARY_TARGET}" /dev/null)
    set_target_properties("${BINARY_TARGET}" PROPERTIES LINKER_LANGUAGE CXX)
    message("    dependency: ${TARGET_PATH}")
    flatten_path("${PACKAGE_DIRECTORY}" mkdir_target)
    add_dependencies("${BINARY_TARGET}" "${mkdir_target}")
    target_link_libraries("${BINARY_TARGET}" "${TARGET_PATH}")
    # Prepare test-specific things.
    if("${TARGET_TEST}")
      add_test("${BINARY_TARGET}" "${BINARY_TARGET}")
    endif()
  endif()
endfunction()

function(cc_binary)
  cc_library(BINARY ${ARGN})
endfunction()

function(cc_test)
  cc_binary(TEST ${ARGN})
endfunction()

function(proto_library)
  # Parse function arguments.
  set(onevalue_options NAME)
  set(multivalue_options SOURCES DEPENDENCIES)
  cmake_parse_arguments(
      TARGET
      "${novalue_options}" "${onevalue_options}" "${multivalue_options}"
      "${ARGN}"
  )

  # Prepare a target path.
  set(TARGET_PATH "${PACKAGE_DIRECTORY}/${TARGET_NAME}.proto_library")
  message("  target: ${TARGET_PATH}")
  flatten_path("${TARGET_PATH}" TARGET_PATH)
  # Prepare source lists.
  set(sources)
  set(cc_sources)
  foreach(source ${TARGET_SOURCES})
    message("    source: ${source}")
    set(source "${PACKAGE_DIRECTORY}/${source}")
    string(REGEX REPLACE "\\.proto$" ".pb.cc" cc_source "${source}")
    string(REGEX REPLACE "\\.proto$" ".pb.h" h_source "${source}")
    list(APPEND cc_sources
         "${FLAME_BINARY_ROOT}/${cc_source}" "${FLAME_BINARY_ROOT}/${h_source}")
    if(NOT EXISTS "${FLAME_BINARY_ROOT}/${cc_source}" OR
       NOT EXISTS "${FLAME_BINARY_ROOT}/${h_source}")
      message(STATUS "Rebuild: ${source}")
      list(APPEND sources "${source}")
    endif()
  endforeach()
  if(NOT "${sources}" STREQUAL "")
    execute_process(
        COMMAND mkdir -p "${FLAME_BINARY_ROOT}/${PACKAGE_DIRECTORY}"
        COMMAND
            ${FLAME_LIBRARY_BINARY_ROOT}/bin/protoc
                --proto_path=depot
                --cpp_out=${FLAME_BINARY_ROOT}/depot
                ${sources}
        WORKING_DIRECTORY "${FLAME_ROOT}"
    )
  endif()

  set(CC_TARGET_PATH "${PACKAGE_DIRECTORY}/${TARGET_NAME}.cc_library")
  flatten_path("${CC_TARGET_PATH}" CC_TARGET_PATH)
  add_library("${CC_TARGET_PATH}" STATIC ${cc_sources})
  target_link_libraries("${CC_TARGET_PATH}" "protobuf" "z")

  # Prepare dependencies.
  parse_dependencies(${TARGET_DEPENDENCIES})
  # Link external dependencies.  They are specified using "#" in the
  # DEPENDENCIES field.
  if(NOT "${LIBRARY_DEPENDENCIES}" STREQUAL "")
    message(FATAL_ERROR "proto_library cannot have library dependencies")
  endif()
  # Treat all dependencies as cc_library.
  if(NOT "${DEPENDENCIES}" STREQUAL "")
    foreach(dependency ${DEPENDENCIES})
      flatten_path("${dependency}.cc_library" dependency)
      target_link_libraries("${TARGET_PATH}" "${dependency}")
    endforeach()
  endif()
endfunction()

################################################################################
# Utility Functions for Flame
################################################################################

# Parses a DEPENDENCIES field.
function(parse_dependencies)
  set(dependencies)
  set(library_dependencies)
  foreach(dependency ${ARGN})
    string(LENGTH "${dependency}" dependency_length)
    string(SUBSTRING "${dependency}" 0 1 dependency_prefix)
    math(EXPR length "${dependency_length}-1")
    if("${dependency_prefix}" STREQUAL "#")
      string(SUBSTRING "${dependency}" 1 "${length}" dependency)
      list(APPEND library_dependencies "${dependency}")
    elseif("${dependency_prefix}" STREQUAL "/")
      string(SUBSTRING "${dependency}" 0 2 dependency_prefix)
      if(NOT "${dependency_prefix}" STREQUAL "//")
        message(FATAL_ERROR "Bad depndency: ${dependency}")
      endif()
      math(EXPR length "${dependency_length}-2")
      string(SUBSTRING "${dependency}" 2 "${length}" dependency)
      list(LENGTH dependency dependency_part_length)
      if(NOT "${dependency_part_length}" EQUAL 1)
        message(FATAL_ERROR "Dependency should not have semi colons.")
      endif()
      set(dependency "depot/${dependency}")
      string(REPLACE ":" ";" dependency "${dependency}")
      list(LENGTH dependency dependency_part_length)
      if("${dependency_part_length}" EQUAL 1)
        string(REPLACE "/" ";" dependency "${dependency}")
        list(LENGTH dependency dependency_part_length)
        math(EXPR last_position "${dependency_part_length}-1")
        list(GET dependency "${last_position}" last_part)
        list(APPEND dependency "${last_part}")
        string(REPLACE ";" "/" dependency "${dependency}")
        list(APPEND dependencies "${dependency}")
      elseif("${dependency_part_length}" EQUAL 2)
        string(REPLACE ";" "/" dependency "${dependency}")
        list(APPEND dependencies "${dependency}")
      else()
        message(FATAL_ERROR "Dependency should not have more than one colons.")
      endif()
    elseif("${dependency_prefix}" STREQUAL ":")
      string(SUBSTRING "${dependency}" 1 "${length}" dependency)
      list(APPEND dependencies "${PACKAGE_DIRECTORY}/${dependency}")
    else()
      message(FATAL_ERROR "Bad depndency: ${dependency}")
    endif()
  endforeach()
  set(DEPENDENCIES ${dependencies} PARENT_SCOPE)
  foreach(dependency ${dependencies})
    message("    dependency: ${dependency}")
  endforeach()
  foreach(library_dependency ${library_dependencies})
    message("    library_dependency: ${library_dependency}")
  endforeach()
  set(LIBRARY_DEPENDENCIES ${library_dependencies} PARENT_SCOPE)
endfunction()

# Finds paths having BUILD.cmake under the directory.  Uses the
# TARGET_DIRECTORIES variable as a return value.
function(find_target_directories directory)
  # Initialize the return value first.
  set(TARGET_DIRECTORIES PARENT_SCOPE)
  # Initialize local variables.
  set(sub_target_directories)
  # Return immediately iff this target is not directory.
  if(NOT EXISTS "${directory}/")
    return()
  endif()
  # Check if the directory has BUILD.cmake.  Append the directory into
  # sub_target_directories iff the directory has BUILD.cmake.
  file(GLOB cmake_target "${directory}/BUILD.cmake")
  foreach(target ${cmake_target})
    string(LENGTH "${target}" target_length)
    string(LENGTH "${FLAME_ROOT}/" prefix_length)
    string(LENGTH "/BUILD.cmake" suffix_length)
    math(EXPR length "${target_length}-${suffix_length}-${prefix_length}")
    string(SUBSTRING
           "${target}" "${prefix_length}" "${length}" target_directory)
    list(APPEND sub_target_directories "${target_directory}")
  endforeach()
  # Call find_target_directories against child directories, and append
  # their results into sub_target_directories.
  file(GLOB sub_directories "${directory}/*")
  foreach(sub_directory ${sub_directories})
    find_target_directories("${sub_directory}")
    foreach(target_directory ${TARGET_DIRECTORIES})
      list(APPEND sub_target_directories "${target_directory}")
    endforeach()
  endforeach()
  # Assign sub_target_directories into TARGET_DIRECTORIES of the parent scope.
  set(TARGET_DIRECTORIES ${sub_target_directories} PARENT_SCOPE)
endfunction()

# Removes "/" from a file path ${path}, and outputs a path into ${output}.  C++
# library files should not have any slashes, so this replaces "/" with "__".
function(flatten_path path output)
  string(REPLACE "/" "__" path "${path}")
  set("${output}" "${path}" PARENT_SCOPE)
endfunction()

################################################################################
# Flame Functions
################################################################################

# Find an external library in flame-library-binary/lib.
function(flame_find_external_library variable library)
  set(temporary_variable ${variable}_${library})
  unset(${temporary_variable} CACHE)
  find_library(${temporary_variable}
               NAMES lib${library}.a lib${library}.la ${library}
               PATHS "${FLAME_LIBRARY_BINARY_ROOT}/lib" NO_DEFAULT_PATH)
  if("${temporary_variable}" STREQUAL "${temporary_variable}-NOTFOUND")
    set(${variable} "${variable}-NOTFOUND" PARENT_SCOPE)
  else()
    set(${variable} ${${temporary_variable}} PARENT_SCOPE)
  endif()
endfunction()

# Check if all the specified libraries exist in flame-library-binary/lib.
function(flame_find_external_libraries libraries output)
  set("${output}" FALSE PARENT_SCOPE)
  foreach(library ${libraries})
    flame_find_external_library(library_path ${library})
    if("${library_path}" STREQUAL "library_path-NOTFOUND")
      return()
    endif()
  endforeach()
  set("${output}" TRUE PARENT_SCOPE)
  foreach(library ${libraries})
    flame_find_external_library(library_path "${library}")
    message(STATUS "Library: ${library} -> ${library_path}")
    add_library("${library}" STATIC IMPORTED)
    set_target_properties(
        "${library}" PROPERTIES IMPORTED_LOCATION "${library_path}")
  endforeach()
endfunction()

# Install libraries by fetching from external repositories.
function(flame_link_external_library)
  # Parse function arguments.
  set(novalue_options)
  set(onevalue_options NAME INSTALLER URL)
  set(multivalue_options LIBRARIES COMMAND INSTALL_COMMAND CONFIGURE_ARGS)
  cmake_parse_arguments(
      TARGET
      "${novalue_options}" "${onevalue_options}" "${multivalue_options}"
      "${ARGN}"
  )

  # Check if there already exist libraries.
  flame_find_external_libraries("${TARGET_LIBRARIES}" libraries_exist)
  if("${libraries_exist}")
    return()
  endif()

  set(configure_target)
  set(configure_command)
  if("${TARGET_INSTALLER}" STREQUAL "configure")
    set(configure_target "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}/configure")
    set(configure_command
        "${configure_target}" --prefix=${FLAME_LIBRARY_BINARY_ROOT}
        ${TARGET_CONFIGURE_ARGS})
  elseif("${TARGET_INSTALLER}" STREQUAL "cmake")
    set(configure_target "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}/CMakeLists.txt")
    set(configure_command
        cmake -DCMAKE_INSTALL_PREFIX=${FLAME_LIBRARY_BINARY_ROOT} 
        "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}" ${TARGET_CONFIGURE_ARGS})
  elseif("${TARGET_INSTALLER}" STREQUAL "boost")
    set(configure_target "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}/bootstrap.sh")
    set(configure_command)
  else()
    message(FATAL_ERROR "unknown installer: ${TARGET_INSTALLER}")
  endif()

  # Prepare source files.
  if(NOT EXISTS "${configure_target}")
    if("${TARGET_URL}" STREQUAL "")
      execute_process(COMMAND ${TARGET_COMMAND})
    else()
      message("${FLAME_LIBRARY_ROOT}/${TARGET_NAME}")
      execute_process(
          COMMAND mkdir -p "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}"
          COMMAND curl -o "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}.tar.xz"
                          "${TARGET_URL}"
      )
      execute_process(
          COMMAND tar Jxvf "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}.tar.xz"
          WORKING_DIRECTORY "${FLAME_LIBRARY_ROOT}/${TARGET_NAME}"
      )
    endif()
    if(NOT EXISTS "${configure_target}")
      message(FATAL_ERROR "failed to fetch: ${configure_target}")
    endif()
  endif()

  execute_process(
      COMMAND mkdir -p "${FLAME_LIBRARY_BINARY_ROOT}/${TARGET_NAME}")
  if(NOT "${configure_command}" STREQUAL "")
    execute_process(
        COMMAND ${configure_command}
        WORKING_DIRECTORY "${FLAME_LIBRARY_BINARY_ROOT}/${TARGET_NAME}")
  endif()
  message("DEBUG: ${TARGET_INSTALL_COMMAND}")
  if("${TARGET_INSTALL_COMMAND}" STREQUAL "")
    set(TARGET_INSTALL_COMMAND make -j 8 install)
  endif()
  execute_process(
      COMMAND ${TARGET_INSTALL_COMMAND}
      WORKING_DIRECTORY "${FLAME_LIBRARY_BINARY_ROOT}/${TARGET_NAME}")

  flame_find_external_libraries("${TARGET_LIBRARIES}" libraries_exist)
  if(NOT "${libraries_exist}")
    message(FATAL_ERROR "failed to prepare: ${TARGET_LIBRARIES}")
  endif()
endfunction()

################################################################################
# Main Function
################################################################################

function(main)
  if(EXISTS "${FLAME_ROOT}/configure.flame")
    message(STATUS "Loadting configure.flame...")
    include("${FLAME_ROOT}/configure.flame")
  endif()

  find_target_directories("${FLAME_ROOT}/depot")
  foreach(PACKAGE_DIRECTORY ${TARGET_DIRECTORIES})
    string(REPLACE "/" "." PACKAGE_PREFIX "${PACKAGE_DIRECTORY}")
    message("Package: ${PACKAGE_DIRECTORY}")
    flatten_path("${PACKAGE_DIRECTORY}" mkdir_target)
    add_custom_target("${mkdir_target}__all")
    add_custom_target(
        "${mkdir_target}" COMMAND mkdir -p "flame-binary/${PACKAGE_DIRECTORY}")
    include("${FLAME_ROOT}/${PACKAGE_DIRECTORY}/BUILD.cmake")
  endforeach()
endfunction()

main()
