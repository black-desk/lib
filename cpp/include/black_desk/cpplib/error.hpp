#pragma once

#include <cassert>
#include <exception>
#include <string>

#include <fmt/format.h>

#include "black_desk/cpplib/macro.hpp"

namespace black_desk::cpplib
{

template <typename T>
[[noreturn]] inline void throw_with_nested_if_current_exception(T &&exception)
{
        if (std::current_exception() != nullptr) {
                std::throw_with_nested(std::forward<T>(exception));
        } else {
                throw std::forward<T>(exception);
        }
}

} // namespace black_desk::cpplib

// NOLINTNEXTLINE
#define NESTED_EXCEPTION(...)                                               \
        black_desk::cpplib::throw_with_nested_if_current_exception(         \
                std::runtime_error(                                         \
                        fmt::format(__FILE__ ":" BLACKDESK_CPPLIB_TOSTRING( \
                                __LINE__) " " __VA_ARGS__)));

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
                        assert(false);
                }
                return ctx.out();
        }
};
