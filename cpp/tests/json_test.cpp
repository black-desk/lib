#include <gtest/gtest.h>

#include "black_desk/cpplib/json_optional_field.hpp"
#include "black_desk/cpplib/json_std_optional.hpp"

struct Point1 {
        int x{}, y{};
        std::optional<std::string> tag;
};

BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_OPTIONAL(
        Point1, BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_OPTIONAL(tag), x, y);

struct Point2 {
    private:
        int x{}, y{};
        std::optional<std::string> tag;

    public:
        BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_OPTIONAL(
                Point2, BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_OPTIONAL(tag), x,
                y);
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
