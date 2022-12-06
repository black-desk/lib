#pragma once

namespace black_desk::cpplib::Linux
{
class FileDescriptorHolder {
    public:
        static FileDescriptorHolder hold(int fd);
        virtual ~FileDescriptorHolder() noexcept;
        FileDescriptorHolder(const FileDescriptorHolder &that) = delete;
        FileDescriptorHolder(FileDescriptorHolder &&that);
        int fd = 0;

    private:
        explicit FileDescriptorHolder(int fd) noexcept;
};
}
