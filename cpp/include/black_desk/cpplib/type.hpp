#include <type_traits>

namespace black_desk::cpplib
{

template <typename T>
using add_lvalue_reference_const_t =
        std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<T>>>;

// TODO(black_desk): add_rvalue_reference_t?

}
