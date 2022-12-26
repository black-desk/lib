#include <fcntl.h>

#include <filesystem>

#include "black_desk/cpplib/Linux/fd.hpp"
#include "black_desk/cpplib/Linux/utils.hpp"
#include "black_desk/cpplib/test.hpp"

TEST(Linux, realpath)
{
        auto result = black_desk::cpplib::Linux::realpath(".");
        auto expected = std::filesystem::current_path();
        ASSERT_EQ(result.string(), expected.string());

        int cwd_fd = open(".", O_PATH);
        {
                auto holder =
                        black_desk::cpplib::Linux::FileDescriptorHolder::hold(
                                cwd_fd);
                auto result = black_desk::cpplib::Linux::realpath(holder);
                auto expected = std::filesystem::current_path();
        }
}
