cmake_minimum_required (VERSION 2.8)
project (treelib)
set(CMAKE_C_FLAGS_RELEASE "-O3")

set (treelib_VERSION_MAJOR 1)
set (treelib_VERSION_MINOR 0)
set (treelib_VERSION_PATCH 0)
set (treelib_VERSION_TWEAK 0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_definitions(-std=c++11)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")

enable_testing()

add_subdirectory(test)
