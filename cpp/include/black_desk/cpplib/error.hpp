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
        int indent = 0;
        // NOLINTNEXTLINE
        constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin())
        {
                const auto *iter = ctx.begin();
                for (; iter != ctx.end() && *iter != '}'; iter++) { // NOLINT
                        if ('0' <= *iter && *iter <= '9') {
                                // NOLINTNEXTLINE
                                indent = indent * 10 + (*iter - '0');
                        } else {
                                throw format_error("invalid format");
                        }
                }
                return iter;
        }

        template <typename FormatContext>
        auto format(const std::exception &exception, FormatContext &ctx) const
                -> decltype(ctx.out())
        {
                const std::exception *current_exception = &exception;
                fmt::format_to(ctx.out(), "{}E {}\n", std::string(indent, ' '),
                               current_exception->what());
                try {
                        std::rethrow_if_nested(*current_exception);
                } catch (const std::exception &nestedException) {
                        fmt::format_to(ctx.out(),
                                       fmt::format("{{}}caused by:\n{{:{}}}",
                                                   indent + 1),
                                       std::string(indent, ' '),
                                       nestedException);
                } catch (...) {
                }
                return ctx.out();
        }
};
