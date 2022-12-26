#include "black_desk/cpplib/Linux/rlimit.hpp"

#include <fmt/format.h>

namespace black_desk::cpplib::Linux
{

auto getrlimit(int resource) -> std::shared_ptr<struct rlimit>
{
        auto rlimit_ptr = std::make_shared<struct rlimit>();

        auto ret = ::getrlimit(resource, rlimit_ptr.get());

        if (ret != 0) {
                throw fmt::system_error(errno, "getrlimit [{}]", resource);
        }

        return rlimit_ptr;
}

} // namespace black_desk::cpplib::Linux
