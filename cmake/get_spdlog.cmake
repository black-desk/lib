CPMAddPackage(
  GITHUB_REPOSITORY gabime/spdlog
  VERSION 1.11.0
  OPTIONS "SPDLOG_FMT_EXTERNAL 1"
  GIT_SHALLOW ON
)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSPDLOG_ACTIVE_LEVEL=0")
