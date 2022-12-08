#include "black_desk/cpplib/Linux/libc.hpp"

#include <cstdlib>
#include <vector>

#include <fmt/format.h>
#include <linux/limits.h>

#include "black_desk/cpplib/Linux/fd.hpp"

namespace black_desk::cpplib::Linux::libc
{

auto realpath(const std::filesystem::path &path) -> std::filesystem::path
{
        auto buffer = std::make_shared<std::vector<char>>(PATH_MAX);
        auto *ret = ::realpath(path.c_str(), buffer->data());
        if (ret == nullptr) {
                throw fmt::system_error(errno, "syscall realpath failed");
        }
        return { buffer->data() };
}

auto realpath(const FileDescriptorHolder &fd_holder) -> std::filesystem::path
{
        std::filesystem::path proc_fd_path(
                fmt::format("/proc/self/fd/{}", fd_holder.fd()));
        return realpath(proc_fd_path);
}

} // namespace black_desk::cpplib::Linux::libc
