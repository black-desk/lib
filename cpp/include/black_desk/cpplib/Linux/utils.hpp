#pragma once

#include <fcntl.h>

#include <filesystem>

namespace black_desk::cpplib::Linux
{

class FileDescriptorHolder;

auto realpath(const std::filesystem::path &path) -> std::filesystem::path;
auto realpath(const FileDescriptorHolder &fd_holder) -> std::filesystem::path;

auto open_path(const std::filesystem::path &path, int flag = O_PATH)
        -> FileDescriptorHolder;

} // namespace black_desk::cpplib::Linux
