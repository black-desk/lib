add_executable(tests Linux/fd_test.cpp)

target_link_libraries(tests GTest::gtest_main blackdesk_cpplib_linux)

include(GoogleTest)

gtest_discover_tests(tests)
