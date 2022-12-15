#include <gtest/gtest.h>

#include "black_desk/cpplib/json/json_helper.hpp"
#include "black_desk/cpplib/json/std_optional.hpp"
#include "black_desk/cpplib/macro.hpp"

#define REQUIRED BLACKDESK_CPPLIB_LIST
#define OPTIONAL BLACKDESK_CPPLIB_LIST

struct Point1 {
        int x{}, y{};
        std::optional<std::string> tag;
};

BLACKDESK_CPPLIB_JSON_NON_INTRUSIVE(Point1, REQUIRED(x, y), OPTIONAL(tag));

struct Point2 {
    private:
        int x{}, y{};
        std::optional<std::string> tag;

    public:
        BLACKDESK_CPPLIB_JSON_INTRUSIVE(Point2, REQUIRED(x, y), OPTIONAL(tag));
        FRIEND_TEST(Json, OptionalField);
};

TEST(Json, OptionalField) // NOLINT
{
        nlohmann::json json = R"({"x":0,"y":0,"tag":"zero point"})"_json;
        auto point_1 = json.get<Point1>();
        EXPECT_EQ(point_1.x, 0);
        EXPECT_EQ(point_1.y, 0);
        EXPECT_EQ(point_1.tag, "zero point");

        auto point_2 = json.get<Point2>();
        EXPECT_EQ(point_2.x, 0);
        EXPECT_EQ(point_2.y, 0);
        EXPECT_EQ(point_2.tag, "zero point");

        json.erase("tag");

        // NOLINTNEXTLINE
        EXPECT_NO_THROW({
                point_1 = json.get<Point1>();
                EXPECT_EQ(point_1.x, 0);
                EXPECT_EQ(point_1.y, 0);
                EXPECT_EQ(point_1.tag, std::nullopt);

                point_2 = json.get<Point2>();
                EXPECT_EQ(point_2.x, 0);
                EXPECT_EQ(point_2.y, 0);
                EXPECT_EQ(point_2.tag, std::nullopt);
        });

        json.erase("x");

        // NOLINTNEXTLINE
        EXPECT_ANY_THROW({ point_1 = json.get<Point1>(); });

        // NOLINTNEXTLINE
        EXPECT_ANY_THROW({ point_2 = json.get<Point2>(); });
}
