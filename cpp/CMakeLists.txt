cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(
  blackdesk_cpplib
  VERSION 0.1.0
  LANGUAGES CXX
)

if(NOT DEFINED CPM_USE_LOCAL_PACKAGES)
  set(CPM_USE_LOCAL_PACKAGES ON)
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY nlohmann/json
  NAME nlohmann_json
  VERSION 3.11.2
  GIT_SHALLOW ON
)

CPMAddPackage(
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 9.1.0
  GIT_SHALLOW ON
)

CPMAddPackage(
  GITHUB_REPOSITORY docopt/docopt.cpp
  NAME docopt
  GIT_TAG master
  VERSION 0.6.2
  GIT_SHALLOW ON
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DBLACKDESK_CPPLIB_DEBUG")

enable_testing()

include_directories(BEFORE include)

add_subdirectory(include)
add_subdirectory(lib)
