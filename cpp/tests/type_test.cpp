#include <optional>

#include "black_desk/cpplib/type.hpp"

static void static_assert_func()
{
        static_assert(
                std::is_const_v<std::remove_reference_t<
                        black_desk::cpplib::add_lvalue_reference_const_t<
                                decltype(std::optional<int>::value_type())>
                        >>);
}
