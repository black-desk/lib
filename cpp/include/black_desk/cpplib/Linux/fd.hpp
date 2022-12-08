#pragma once

namespace black_desk::cpplib::Linux
{

class FileDescriptorHolder {
    public:
        static auto hold(int file_descriptor) -> FileDescriptorHolder;

        virtual ~FileDescriptorHolder() noexcept;

        FileDescriptorHolder(const FileDescriptorHolder &that) = delete;
        auto operator=(const FileDescriptorHolder &that)
                -> FileDescriptorHolder & = delete;

        FileDescriptorHolder(FileDescriptorHolder &&that) noexcept;
        auto operator=(FileDescriptorHolder &&that) noexcept
                -> FileDescriptorHolder &;

        [[nodiscard]] auto fd() const -> int;

    private:
        explicit FileDescriptorHolder(int file_descriptor) noexcept;
        int file_descriptor = 0;
};

} // namespace black_desk::cpplib::Linux
