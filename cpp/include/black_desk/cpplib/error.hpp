#pragma once

#include <exception>
#include <string>

#include <fmt/format.h>

#define BLACKDESK_CPPLIB_STRINGIFY(x) #x
#define BLACKDESK_CPPLIB_TOSTRING(x) BLACKDESK_CPPLIB_STRINGIFY(x)

// NOLINTNEXTLINE
#define NESTED_EXCEPTION(...)                                  \
        std::throw_with_nested(std::runtime_error(fmt::format( \
                __FILE__                                       \
                ":" BLACKDESK_CPPLIB_TOSTRING(__LINE__) " \t" __VA_ARGS__)))

template <>
struct fmt::formatter<std::exception> {
        // NOLINTNEXTLINE
        constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin())
        {
                return ctx.begin();
        }

        template <typename FormatContext>
        auto format(const std::exception &exception, FormatContext &ctx) const
                -> decltype(ctx.out())
        {
                const std::exception *current_exception = &exception;
                int level = 0;
                bool nested = false;
                do {
                        nested = false;
                        fmt::format_to(ctx.out(), "{}E {}\n",
                                       std::string(level, ' '),
                                       current_exception->what());
                        try {
                                std::rethrow_if_nested(*current_exception);
                        } catch (const std::exception &nestedException) {
                                fmt::format_to(ctx.out(), "{}caused by:\n",
                                               std::string(level, ' '));
                                level++;
                                current_exception = &nestedException;
                                nested = true;
                        } catch (...) {
                        }
                } while (nested);
                return ctx.out();
        }
};
