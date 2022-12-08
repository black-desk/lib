find_package(Git)

execute_process(
  COMMAND ${GIT_EXECUTABLE} describe --abbrev=6 --dirty --always --tags
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(version.hpp.in version.hpp)

# CORE
add_library(
  blackdesk_cpplib_core
  common.cpp logger.cpp
)
target_link_libraries(
  blackdesk_cpplib_core
  PUBLIC spdlog::spdlog
)
target_include_directories(
  blackdesk_cpplib_core
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_features(
  blackdesk_cpplib_core
  PUBLIC cxx_std_17
)
set_property(TARGET blackdesk_cpplib_core PROPERTY CXX_STANDARD 17)

# NOTE(black_desk): This duplication is to make g++ work, check
# <https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#high-level-meta-features-indicating-c-standard-support>
# for further information.
#
# Note If the compiler's default standard level is at least that of the requested feature, CMake may
# omit the -std= flag. The flag may still be added if the compiler's default extensions mode does
# not match the <LANG>_EXTENSIONS target property, or if the <LANG>_STANDARD target property is set.
#
# same below for TARGET blackdesk_cpplib_linux

target_compile_definitions(
  blackdesk_cpplib_core
  PRIVATE SPDLOG_ACTIVE_LEVEL=0
  PRIVATE "$<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=0;BLACKDESK_CPPLIB_DEBUG>"
)

# LINUX
add_library(
  blackdesk_cpplib_linux
  Linux/fd.cpp Linux/libc.cpp
)
target_link_libraries(
  blackdesk_cpplib_linux
  PUBLIC fmt::fmt
  PUBLIC blackdesk_cpplib_core
)
target_include_directories(
  blackdesk_cpplib_linux
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(
  blackdesk_cpplib_linux
  PUBLIC cxx_std_17
)
set_property(TARGET blackdesk_cpplib_linux PROPERTY CXX_STANDARD 17)
target_compile_definitions(
  blackdesk_cpplib_linux
  PRIVATE "$<$<CONFIG:Debug>:SPDLOG_ACTIVE_LEVEL=0;BLACKDESK_CPPLIB_DEBUG>"
)
