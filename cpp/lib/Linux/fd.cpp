#include "black_desk/cpplib/Linux/fd.hpp"

#include <unistd.h>

#include <utility>

#include <fmt/format.h>

#include "black_desk/cpplib/logger.hpp"
#include "black_desk/cpplib/verbose.hpp"

namespace black_desk::cpplib::Linux
{

auto FileDescriptorHolder::hold(int file_descriptor) -> FileDescriptorHolder
{
        BLACKDESK_CPPLIB_VERBOSE_TRACE("hold fd={}", file_descriptor);
        auto ret = FileDescriptorHolder(file_descriptor);
        if (ret.file_descriptor <= 0) {
                throw fmt::system_error(EINVAL,
                                        "Invalid file descriptor number {}",
                                        ret.file_descriptor);
        }

        return ret;
}

FileDescriptorHolder::FileDescriptorHolder(int file_descriptor) noexcept
        : file_descriptor(file_descriptor)
{
}

FileDescriptorHolder::~FileDescriptorHolder() noexcept
{
        if (this->file_descriptor > 0) {
                BLACKDESK_CPPLIB_VERBOSE_TRACE("release fd={}",
                                               this->file_descriptor);
                close(this->file_descriptor);
        }
}

FileDescriptorHolder::FileDescriptorHolder(FileDescriptorHolder &&that) noexcept
        : file_descriptor(that.file_descriptor)
{
        BLACKDESK_CPPLIB_VERBOSE_TRACE("move fd={}", file_descriptor);
        that.file_descriptor = 0;
}

auto FileDescriptorHolder::fd() const -> int
{
        return this->file_descriptor;
}

} // namespace black_desk::cpplib::Linux
