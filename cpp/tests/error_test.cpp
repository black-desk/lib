#include <gtest/gtest.h>

#include "black_desk/cpplib/error.hpp"

TEST(Common, nested_expection_print) // NOLINT
{
        try {
                try { // 1
                        try { // 2
                                std::string empty_string;
                                empty_string.at(1);
                        } catch (...) {
                                std::throw_with_nested(
                                        std::runtime_error("try 2 failed"));
                        }
                } catch (...) {
                        std::throw_with_nested(
                                std::runtime_error("try 1 failed"));
                }
        } catch (const std::exception &exception) {
                std::string what = fmt::format("{}", exception);
                EXPECT_EQ(what, R"(E try 1 failed
caused by:
 E try 2 failed
 caused by:
  E basic_string::at: __n (which is 1) >= this->size() (which is 0)
)");
        }
}

TEST(Common, nested_expection_wrap) // NOLINT
{
        try {
                try { // 1
                        try { // 2
                                EXCEPTION("exception here");
                        } catch (...) {
                                NESTED_EXCEPTION("try 2 failed");
                        }
                } catch (...) {
                        NESTED_EXCEPTION("try 1 failed");
                }
        } catch (const std::exception &exception) {
                std::string what = fmt::format("{}", exception);
                EXPECT_NE(what.find("41"), std::string::npos)
                        << "should found line number of try 1";
                EXPECT_NE(what.find("try 1 failed"), std::string::npos)
                        << "should found try 1 message";

                EXPECT_NE(what.find("38"), std::string::npos)
                        << "should found line number of try 2";
                EXPECT_NE(what.find("try 2 failed"), std::string::npos)
                        << "should found try 2 message";

                EXPECT_NE(what.find("36"), std::string::npos)
                        << "should found line number of exception";
                EXPECT_NE(what.find("exception here"), std::string::npos)
                        << "should found exception message";

                EXPECT_NE(what.find("error_test.cpp"), std::string::npos)
                        << "should found file name";
        }
}
