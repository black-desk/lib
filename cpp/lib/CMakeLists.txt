find_package(Git)

execute_process(
  COMMAND ${GIT_EXECUTABLE} describe --abbrev=6 --dirty --always --tags
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(version.hpp.in version.hpp)

add_library(blackdesk_cpplib_core common.cpp logger.cpp)
add_library(blackdesk_cpplib_linux Linux/fd.cpp)

target_link_libraries(blackdesk_cpplib_core spdlog::spdlog)
target_link_libraries(blackdesk_cpplib_linux fmt::fmt blackdesk_cpplib_core)
