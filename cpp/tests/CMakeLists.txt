add_executable(
  blackdesk_cpplib_tests
  Linux/fd_test.cpp
)

target_link_libraries(
  blackdesk_cpplib_tests
  PRIVATE GTest::gtest_main
  PRIVATE blackdesk_cpplib_linux
)

include(GoogleTest)

gtest_discover_tests(blackdesk_cpplib_tests)
