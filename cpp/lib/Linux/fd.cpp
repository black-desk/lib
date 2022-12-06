#include "black_desk/cpplib/Linux/fd.hpp"

#include <unistd.h>

#include <utility>

#include <fmt/format.h>

#include "black_desk/cpplib/verbose.hpp"

namespace black_desk::cpplib::Linux
{

FileDescriptorHolder FileDescriptorHolder::hold(int fd)
{
        BLACKDESK_CPPLIB_VERBOSE("hold fd={}", fd);
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
                BLACKDESK_CPPLIB_VERBOSE("release fd={}", fd);
                close(fd);
        }
}

FileDescriptorHolder::FileDescriptorHolder(FileDescriptorHolder &&that)
{
        BLACKDESK_CPPLIB_VERBOSE("move fd={}", fd);
        this->fd = that.fd;
        that.fd = 0;
}

}
