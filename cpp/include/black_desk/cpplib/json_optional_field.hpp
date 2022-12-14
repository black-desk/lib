#pragma once

#include <nlohmann/json.hpp>

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_OPTIONAL(     \
        Type, OptionalFields, ...)                                             \
        inline void to_json(nlohmann::json &nlohmann_json_j,                   \
                            const Type &nlohmann_json_t)                       \
        {                                                                      \
                NLOHMANN_JSON_EXPAND(                                          \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, OptionalFields)) \
                NLOHMANN_JSON_EXPAND(                                          \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__))    \
        }                                                                      \
        inline void from_json(const nlohmann::json &nlohmann_json_j,           \
                              Type &nlohmann_json_t)                           \
        {                                                                      \
                Type nlohmann_json_default_obj;                                \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(                      \
                        NLOHMANN_JSON_FROM_WITH_DEFAULT, OptionalFields))      \
                NLOHMANN_JSON_EXPAND(                                          \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))  \
        }

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_OPTIONAL(         \
        Type, OptionalFields, ...)                                             \
        friend void to_json(nlohmann::json &nlohmann_json_j,                   \
                            const Type &nlohmann_json_t)                       \
        {                                                                      \
                NLOHMANN_JSON_EXPAND(                                          \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, OptionalFields)) \
                NLOHMANN_JSON_EXPAND(                                          \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__))    \
        }                                                                      \
        friend void from_json(const nlohmann::json &nlohmann_json_j,           \
                              Type &nlohmann_json_t)                           \
        {                                                                      \
                Type nlohmann_json_default_obj;                                \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(                      \
                        NLOHMANN_JSON_FROM_WITH_DEFAULT, OptionalFields))      \
                NLOHMANN_JSON_EXPAND(                                          \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__))  \
        }

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_NLOHMANN_DEFINE_TYPE_OPTIONAL(...) __VA_ARGS__
