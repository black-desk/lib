#include "black_desk/cpplib/Linux/utils.hpp"

#include <fcntl.h>

#include <cstdlib>
#include <filesystem>
#include <vector>

#include <fmt/format.h>
#include <linux/limits.h>

#include "black_desk/cpplib/Linux/fd.hpp"
#include "black_desk/cpplib/logger.hpp"
#include "black_desk/cpplib/verbose.hpp"

namespace black_desk::cpplib::Linux
{

auto realpath(const std::filesystem::path &path) -> std::filesystem::path
{
        auto buffer = std::make_shared<std::vector<char>>(PATH_MAX);
        auto *ret = ::realpath(path.c_str(), buffer->data());
        if (ret == nullptr) {
                throw fmt::system_error(errno, "realpath [\"{}\"]",
                                        path.string());
        }
        return { buffer->data() };
}

auto realpath(const FileDescriptorHolder &fd_holder) -> std::filesystem::path
{
        std::filesystem::path proc_fd_path(
                fmt::format("/proc/self/fd/{}", fd_holder.fd()));
        return realpath(proc_fd_path);
}

static void open_path_flag_check(int &flag);

auto open_path(const std::filesystem::path &path, int flag)
        -> FileDescriptorHolder
{
        open_path_flag_check(flag);
        auto ret = ::open(path.c_str(), O_PATH);
        if (ret == -1) {
                throw fmt::system_error(errno, "open [\"{}\", O_PATH]",
                                        path.string());
        }
        return FileDescriptorHolder::hold(ret);
}

void open_path_flag_check(int &flag)
{
        if ((flag & O_PATH) == 0) {
                BLACKDESK_CPPLIB_VERBOSE_WARN(
                        "open_path called without O_PATH in flag");
        }

        flag &= O_PATH;

        if ((flag & ~(O_PATH | O_CLOEXEC | O_DIRECTORY | O_NOFOLLOW)) != 0) {
                BLACKDESK_CPPLIB_VERBOSE_WARN(
                        "open_path called with ignored flag bits");
        }
}

} // namespace black_desk::cpplib::Linux
