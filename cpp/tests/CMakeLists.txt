add_executable(blackdesk_cpplib_tests)

file(GLOB_RECURSE BLACKDESK_CPPLIB_TESTS_SOURCE FOLLOW_SYMLINKS CONFIGURE_DEPENDS *.cpp *.h)

target_sources(
  blackdesk_cpplib_tests
  PRIVATE ${BLACKDESK_CPPLIB_TESTS_SOURCE}
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
