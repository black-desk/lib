#pragma once

#include <nlohmann/json.hpp>

#include "black_desk/cpplib/macro.hpp"

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_JSON_NON_INTRUSIVE(Type, Required, Optional) \
        inline void to_json(nlohmann::json &nlohmann_json_j,          \
                            const Type &nlohmann_json_t)              \
        {                                                             \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(             \
                        NLOHMANN_JSON_TO,                             \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Required)))    \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(             \
                        NLOHMANN_JSON_TO,                             \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Optional)))    \
        }                                                             \
        inline void from_json(const nlohmann::json &nlohmann_json_j,  \
                              Type &nlohmann_json_t)                  \
        {                                                             \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(             \
                        NLOHMANN_JSON_FROM,                           \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Required)))    \
                Type nlohmann_json_default_obj;                       \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(             \
                        NLOHMANN_JSON_FROM_WITH_DEFAULT,              \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Optional)))    \
        }

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_JSON_INTRUSIVE(Type, Required, Optional)    \
        friend void to_json(nlohmann::json &nlohmann_json_j,         \
                            const Type &nlohmann_json_t)             \
        {                                                            \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(            \
                        NLOHMANN_JSON_TO,                            \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Required)))   \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(            \
                        NLOHMANN_JSON_TO,                            \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Optional)))   \
        }                                                            \
        friend void from_json(const nlohmann::json &nlohmann_json_j, \
                              Type &nlohmann_json_t)                 \
        {                                                            \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(            \
                        NLOHMANN_JSON_FROM,                          \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Required)))   \
                Type nlohmann_json_default_obj;                      \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(            \
                        NLOHMANN_JSON_FROM_WITH_DEFAULT,             \
                        BLACKDESK_CPPLIB_REMOVE_PARENS(Optional)))   \
        }
