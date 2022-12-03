#include "black_desk/cpplib/Linux/fd.hpp"

#include <unistd.h>

#include <utility>

#include <fmt/format.h>

namespace black_desk::cpplib::Linux
{

FileDescriptorHolder FileDescriptorHolder::hold(int fd)
{
        auto ret = FileDescriptorHolder(fd);
        if (ret.fd <= 0) {
                throw fmt::system_error(
                        EINVAL, "Invalid file descriptor number {}", ret.fd);
        }

        return ret;
}

FileDescriptorHolder::FileDescriptorHolder(int fd) noexcept
        : fd(fd)
{
}

FileDescriptorHolder::~FileDescriptorHolder() noexcept
{
        if (fd > 0) {
                close(fd);
        }
}

FileDescriptorHolder::FileDescriptorHolder(FileDescriptorHolder &&that)
{
        this->fd = that.fd;
        that.fd = 0;
}

}
