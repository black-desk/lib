#pragma once

#include <string>
#include <vector>

#include <fmt/format.h>
namespace black_desk::cpplib
{

inline auto join(const std::vector<std::string> &strs,
                 const std::string &sep = " ") -> std::string
{
        return fmt::format("{}", fmt::join(strs.begin(), strs.end(), sep));
}

}
