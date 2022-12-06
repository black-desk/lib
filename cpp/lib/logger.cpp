#include "black_desk/cpplib/logger.hpp"

#include <map>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>

namespace black_desk::cpplib
{

std::shared_ptr<spdlog::logger> get_logger(const std::string &name)
{
        // Initialize logger

        auto syslog = std::make_shared<spdlog::sinks::syslog_sink_st>(
                name, LOG_PID, LOG_USER, true);
        auto stdlog = std::make_shared<spdlog::sinks::stdout_color_sink_st>();

        syslog->set_pattern("<%s/%!> %#: %v");

        std::array<spdlog::sink_ptr, 2> sinks = {
                syslog,
                stdlog,
        };

        auto logger = std::make_shared<spdlog::logger>(name, begin(sinks),
                                                       end(sinks));

        // Initialize logger level

        const char *level = std::getenv("LOG_LEVEL");

        static auto level_map =
                std::map<std::string, spdlog::level::level_enum>({
                        { "trace", spdlog::level::trace },
                        { "debug", spdlog::level::debug },
                        { "info", spdlog::level::info },
                        { "warn", spdlog::level::warn },
                        { "err", spdlog::level::err },
                        { "critical", spdlog::level::critical },
                        { "off", spdlog::level::off },
                });

        try {
                logger->set_level(level_map.at(level ? level : "off"));
        } catch (const std::range_error &e) {
                logger->set_level(spdlog::level::off);
        }

        return logger;
}

}
