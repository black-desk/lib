cmake_minimum_required(VERSION 3.13.4..3.25.1)

project(
  blackdesk_cpplib
  VERSION 0.1.0
  LANGUAGES CXX
)

include(cmake/dependencies.cmake)

if(NOT DEFINED BLACKDESK_CPPLIB_MASTER_PROJECT)
  if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(BLACKDESK_CPPLIB_MASTER_PROJECT ON)
  else()
    set(BLACKDESK_CPPLIB_MASTER_PROJECT OFF)
  endif()
endif()

if(BLACKDESK_CPPLIB_MASTER_PROJECT)
  if(NOT DEFINED BLACKDESK_CPPLIB_BUILD_TEST)
    set(BLACKDESK_CPPLIB_BUILD_TEST ON)
  endif()
endif()

add_subdirectory(lib)

if(BLACKDESK_CPPLIB_BUILD_TEST)
  enable_testing()
  add_subdirectory(tests)
endif()
