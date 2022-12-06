#include <gtest/gtest.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "black_desk/cpplib/Linux/fd.hpp"

using black_desk::cpplib::Linux::FileDescriptorHolder;

TEST(Linux, FileDescriptorHolder_Basic_RAII)
{
        int fd = open(".", O_PATH);
        {
                auto holder = FileDescriptorHolder::hold(fd);
        }
        int ret = close(fd);
        ASSERT_EQ(ret, -1)
                << "fd should have been closed by holder, close a closed fd should return -1";
        ASSERT_EQ(errno, EBADF)
                << "fd should have been closed by holder, close a closed fd should set errno to EBADF(9)";
}

TEST(Linux, FileDescriptorHolder_Move)
{
        int fd = open(".", O_PATH);

        ASSERT_TRUE(fd > 0) << "open pwd should always work";

        {
                std::unique_ptr<FileDescriptorHolder> ptr;
                {
                        auto holder = FileDescriptorHolder::hold(fd);
                        ptr = std::make_unique<FileDescriptorHolder>(
                                std::move(holder));
                }

                ASSERT_TRUE(ptr) << "ptr should point to moved holder";

                ASSERT_EQ(ptr->fd, fd)
                        << "fd got from holder should equal to ret of open";
        }

        int ret = close(fd);
        ASSERT_EQ(ret, -1)
                << "fd should have been closed by ptr, close a closed fd should return -1";
        ASSERT_EQ(errno, EBADF)
                << "fd should have been closed by ptr, close a closed fd should set errno to EBADF(9)";
}
