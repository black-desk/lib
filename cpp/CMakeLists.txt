cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(
  blackdesk_cpplib
  VERSION 0.1.0
  LANGUAGES CXX
)

include(cmake/dependencies.cmake)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DBLACKDESK_CPPLIB_DEBUG")

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRE)
set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")

enable_testing()

include_directories(BEFORE include)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(tests)
