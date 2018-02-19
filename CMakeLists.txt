cmake_minimum_required(VERSION 3.9)

project(selena)

include(CTest)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

# ---[ Color diagnostics
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
endif()

# the following allows to reference header files in "<" ">" (e.g., #include <dsms/../index.h>)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include)

add_subdirectory(dsms)
add_subdirectory(generic_client)
add_subdirectory(googletest)
add_subdirectory(unit_tests)