#pragma once

#include <filesystem>

namespace black_desk::cpplib::Linux
{

class FileDescriptorHolder;

auto realpath(const std::filesystem::path &path) -> std::filesystem::path;
auto realpath(const FileDescriptorHolder &fd_holder) -> std::filesystem::path;

} // namespace black_desk::cpplib::Linux
