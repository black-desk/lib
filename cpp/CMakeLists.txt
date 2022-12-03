cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(
  blackdesk_cpplib
  VERSION 0.1.0
  LANGUAGES CXX
)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME nlohmann_json
  GIT_TAG master
  GITHUB_REPOSITORY nlohmann/json
  GIT_SHALLOW ON
)

CPMAddPackage(
  NAME fmt
  GIT_TAG master
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_SHALLOW ON
)

CPMAddPackage(
  NAME docopt
  GIT_TAG master
  GITHUB_REPOSITORY docopt/docopt.cpp
  GIT_SHALLOW ON
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DBLACKDESK_CPPLIB_DEBUG")

enable_testing()

include_directories(BEFORE include)

add_subdirectory(include)
add_subdirectory(lib)
