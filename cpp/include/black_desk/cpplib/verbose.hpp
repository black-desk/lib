#pragma once

#ifdef BLACKDESK_CPPLIB_DEBUG

#include <spdlog/spdlog.h>

#include "black_desk/cpplib/logger.hpp"

#define BLACKDESK_CPPLIB_VERBOSE(...) \
        SPDLOG_LOGGER_TRACE(black_desk::cpplib::verbose_logger(), __VA_ARGS__)

#else

#define BLACKDESK_CPPLIB_VERBOSE(...) (void)0

#endif
