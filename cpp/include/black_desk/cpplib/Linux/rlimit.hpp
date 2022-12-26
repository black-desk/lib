#pragma once

#include <sys/resource.h>

#include <memory>

namespace black_desk::cpplib::Linux
{

auto getrlimit(int resource) -> std::shared_ptr<struct rlimit>;

}
