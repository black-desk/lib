#pragma once

#include <spdlog/spdlog.h>

#include "black_desk/cpplib/common.hpp"

namespace black_desk::cpplib
{

std::shared_ptr<spdlog::logger> get_logger(const std::string &name);

inline void init_default_logger(const std::string &name)
{
        auto logger = get_logger(name);
        spdlog::set_default_logger(logger);
}

#ifdef BLACKDESK_CPPLIB_DEBUG

inline std::shared_ptr<spdlog::logger> verbose_logger()
{
        static std::shared_ptr<spdlog::logger> logger = []() -> auto
        {
                auto logger = get_logger("black_desk/cpplib");
                SPDLOG_LOGGER_INFO(logger, "version {}", VERSION);
                return logger;
        }
        ();
        return logger;
}

#endif

} // namespace linglong::box::util
