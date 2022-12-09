add_executable(
  blackdesk_cpplib_tests
  Linux/fd_test.cpp Linux/utils_test.cpp
)

target_link_libraries(
  blackdesk_cpplib_tests
  PRIVATE GTest::gtest_main
  PRIVATE blackdesk_cpplib_linux
)
set_property(TARGET blackdesk_cpplib_tests PROPERTY CXX_STANDARD 17)

include(GoogleTest)

gtest_discover_tests(blackdesk_cpplib_tests)
