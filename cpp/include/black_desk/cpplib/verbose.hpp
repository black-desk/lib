#pragma once

#ifdef BLACKDESK_CPPLIB_DEBUG

#include <spdlog/spdlog.h>

#define BLACKDESK_CPPLIB_VERBOSE_TRACE(...) \
        SPDLOG_LOGGER_TRACE(black_desk::cpplib::verbose_logger(), __VA_ARGS__)
#define BLACKDESK_CPPLIB_VERBOSE_DEBUG(...) \
        SPDLOG_LOGGER_DEBUG(black_desk::cpplib::verbose_logger(), __VA_ARGS__)
#define BLACKDESK_CPPLIB_VERBOSE_INFO(...) \
        SPDLOG_LOGGER_INFO(black_desk::cpplib::verbose_logger(), __VA_ARGS__)
#define BLACKDESK_CPPLIB_VERBOSE_WARN(...) \
        SPDLOG_LOGGER_WARN(black_desk::cpplib::verbose_logger(), __VA_ARGS__)
#define BLACKDESK_CPPLIB_VERBOSE_ERROR(...) \
        SPDLOG_LOGGER_ERROR(black_desk::cpplib::verbose_logger(), __VA_ARGS__)
#define BLACKDESK_CPPLIB_VERBOSE_CRITICAL(...)                       \
        SPDLOG_LOGGER_CRITICAL(black_desk::cpplib::verbose_logger(), \
                               __VA_ARGS__)
#else

#define BLACKDESK_CPPLIB_VERBOSE_TRACE(...) (void)0
#define BLACKDESK_CPPLIB_VERBOSE_DEBUG(...) (void)0
#define BLACKDESK_CPPLIB_VERBOSE_INFO(...) (void)0
#define BLACKDESK_CPPLIB_VERBOSE_WARN(...) (void)0
#define BLACKDESK_CPPLIB_VERBOSE_ERROR(...) (void)0
#define BLACKDESK_CPPLIB_VERBOSE_CRITICAL(...) (void)0

#endif
