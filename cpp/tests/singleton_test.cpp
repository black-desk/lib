#include "TestSingleton.hpp"
#include "black_desk/cpplib/test.hpp"

TEST(Singleton, Basics)
{
        {
                TestSingleton a;
                a->a = 1;
                a->b = 2;
                EXPECT_EQ(a->add(), 3);
        }

        TestSingleton b;
        EXPECT_EQ(b->a, 1);
        EXPECT_EQ(b->b, 2);
        EXPECT_EQ(b->add(), 3);
}
