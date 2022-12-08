#pragma once

#include <spdlog/spdlog.h>

#ifdef BLACKDESK_CPPLIB_DEBUG
#include "black_desk/cpplib/common.hpp"
#endif

namespace black_desk::cpplib
{

auto get_logger(const std::string &name) noexcept
        -> std::shared_ptr<spdlog::logger>;

inline void init_default_logger(const std::string &name)
{
        auto logger = get_logger(name);
        spdlog::set_default_logger(logger);
}

#ifdef BLACKDESK_CPPLIB_DEBUG

inline auto create_verbose_logger() -> std::shared_ptr<spdlog::logger>
{
        auto logger = get_logger("black_desk/cpplib");
        SPDLOG_LOGGER_INFO(logger, "version {}", VERSION);
        return logger;
}

inline auto verbose_logger() noexcept -> std::shared_ptr<spdlog::logger>
{
        static std::shared_ptr<spdlog::logger> verbose_logger =
                create_verbose_logger();
        return verbose_logger;
}

#endif

} // namespace black_desk::cpplib
