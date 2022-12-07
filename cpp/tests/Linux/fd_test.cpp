#include <gtest/gtest.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "black_desk/cpplib/Linux/fd.hpp"

using black_desk::cpplib::Linux::FileDescriptorHolder;

TEST(Linux, FileDescriptorHolderBasicRAII) // NOLINT
{
        int cwd_fd = open(".", O_PATH);
        {
                auto holder = FileDescriptorHolder::hold(cwd_fd);
        }
        int ret = close(cwd_fd);
        ASSERT_EQ(ret, -1)
                << "fd should have been closed by holder, close a closed fd should return -1";
        ASSERT_EQ(errno, EBADF)
                << "fd should have been closed by holder, close a closed fd should set errno to EBADF(9)";
}

TEST(Linux, FileDescriptorHolderMove) // NOLINT
{
        int cwd_fd = open(".", O_PATH);

        ASSERT_TRUE(cwd_fd > 0) << "open pwd should always work";

        {
                std::unique_ptr<FileDescriptorHolder> ptr;
                {
                        auto holder = FileDescriptorHolder::hold(cwd_fd);
                        ptr = std::make_unique<FileDescriptorHolder>(
                                std::move(holder));
                }

                ASSERT_TRUE(ptr) << "ptr should point to moved holder";

                ASSERT_EQ(ptr->file_descriptor, cwd_fd)
                        << "fd got from holder should equal to ret of open";
        }

        int ret = close(cwd_fd);
        ASSERT_EQ(ret, -1)
                << "fd should have been closed by ptr, close a closed fd should return -1";
        ASSERT_EQ(errno, EBADF)
                << "fd should have been closed by ptr, close a closed fd should set errno to EBADF(9)";
}
