#pragma once

#include <nlohmann/json.hpp>

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_JSON_NON_INTRUSIVE(Type, Required, Optional)      \
        inline void to_json(nlohmann::json &nlohmann_json_j,               \
                            const Type &nlohmann_json_t)                   \
        {                                                                  \
                NLOHMANN_JSON_EXPAND(                                      \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, Required))   \
                NLOHMANN_JSON_EXPAND(                                      \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, Optional))   \
        }                                                                  \
        inline void from_json(const nlohmann::json &nlohmann_json_j,       \
                              Type &nlohmann_json_t)                       \
        {                                                                  \
                NLOHMANN_JSON_EXPAND(                                      \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, Required)) \
                Type nlohmann_json_default_obj;                            \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(                  \
                        NLOHMANN_JSON_FROM_WITH_DEFAULT, Optional))        \
        }

// NOLINTNEXTLINE
#define BLACKDESK_CPPLIB_JSON_INTRUSIVE(Type, Required, Optional)          \
        friend void to_json(nlohmann::json &nlohmann_json_j,               \
                            const Type &nlohmann_json_t)                   \
        {                                                                  \
                NLOHMANN_JSON_EXPAND(                                      \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, Required))   \
                NLOHMANN_JSON_EXPAND(                                      \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, Optional))   \
        }                                                                  \
        friend void from_json(const nlohmann::json &nlohmann_json_j,       \
                              Type &nlohmann_json_t)                       \
        {                                                                  \
                NLOHMANN_JSON_EXPAND(                                      \
                        NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, Required)) \
                Type nlohmann_json_default_obj;                            \
                NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(                  \
                        NLOHMANN_JSON_FROM_WITH_DEFAULT, Optional))        \
        }
