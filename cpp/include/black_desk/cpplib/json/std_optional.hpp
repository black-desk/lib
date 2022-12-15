#pragma once

#include <optional>

#include <nlohmann/json.hpp>

namespace nlohmann
{
template <typename T>
struct adl_serializer<std::optional<T>> {
        static void to_json(json &json, const std::optional<T> &opt)
        {
                if (opt == std::nullopt) {
                        json = nullptr;
                } else {
                        json = *opt;
                }
        }

        static void from_json(const json &json, std::optional<T> &opt)
        {
                if (json.is_null()) {
                        opt = std::nullopt;
                } else {
                        opt = json.get<T>();
                }
        }
};
} // namespace nlohmann
