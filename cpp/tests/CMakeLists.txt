add_executable(
  blackdesk_cpplib_tests Linux/fd_test.cpp Linux/utils_test.cpp error_test.cpp json_test.cpp
                         utils_test.cpp type_test.cpp
)

target_link_libraries(
  blackdesk_cpplib_tests
  PRIVATE GTest::gtest_main
  PRIVATE blackdesk_cpplib_linux
  PRIVATE nlohmann_json::nlohmann_json
)
set_property(TARGET blackdesk_cpplib_tests PROPERTY CXX_STANDARD 17)

include(GoogleTest)

gtest_discover_tests(blackdesk_cpplib_tests)
