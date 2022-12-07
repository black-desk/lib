#include "black_desk/cpplib/Linux/fd.hpp"

#include <unistd.h>

#include <utility>

#include <fmt/format.h>

#include "black_desk/cpplib/verbose.hpp"

namespace black_desk::cpplib::Linux
{

auto FileDescriptorHolder::hold(int file_descriptor) -> FileDescriptorHolder
{
        BLACKDESK_CPPLIB_VERBOSE("hold fd={}", file_descriptor);
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
                BLACKDESK_CPPLIB_VERBOSE("release fd={}",
                                         this->file_descriptor);
                close(this->file_descriptor);
        }
}

FileDescriptorHolder::FileDescriptorHolder(FileDescriptorHolder &&that) noexcept
        : file_descriptor(that.file_descriptor)
{
        BLACKDESK_CPPLIB_VERBOSE("move fd={}", file_descriptor);
        that.file_descriptor = 0;
}

} // namespace black_desk::cpplib::Linux
