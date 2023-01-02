#pragma once

#include <string>
#include <vector>

#include <fmt/format.h>
namespace black_desk::cpplib::strings
{

template <typename T>
auto join(const std::vector<std::string> &strs, const T &sep) -> std::string
{
        return fmt::format("{}", fmt::join(strs.begin(), strs.end(),
                                           std::string{ sep }));
}

inline auto join(const std::vector<std::string> &strs)
{
        return join(strs, ' ');
}

template <typename T>
auto split(const std::string &input, const T &delimiter)
        -> std::vector<std::string>
{
        std::string delim = delimiter;
        size_t pos_start = 0;
        size_t pos_end = -1;
        size_t delim_len = delim.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = input.find(delim, pos_start)) != std::string::npos) {
                token = input.substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.push_back(token);
        }

        res.push_back(input.substr(pos_start));
        return res;
}

} // namespace black_desk::cpplib::strings
