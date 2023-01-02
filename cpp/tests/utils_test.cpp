#include "black_desk/cpplib/test.hpp"
#include "black_desk/cpplib/utils.hpp"

TEST(Utils, Split)
{
        std::string input = "1;;2;;3;;4";
        auto components = black_desk::cpplib::strings::split(input, ";;");
        ASSERT_EQ(components.size(), 4);
        ASSERT_EQ(components[0], "1");
        ASSERT_EQ(components[1], "2");
        ASSERT_EQ(components[2], "3");
        ASSERT_EQ(components[3], "4");
}
