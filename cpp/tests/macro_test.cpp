#include "black_desk/cpplib/macro.hpp"

[[maybe_unused]] static int fn()
{
        static_assert(BLACKDESK_CPPLIB_NOT(0) == true);
        static_assert(BLACKDESK_CPPLIB_NOT(1) == false);

        static_assert(BLACKDESK_CPPLIB_AND(0, 0) == false);
        static_assert(BLACKDESK_CPPLIB_AND(0, 1) == false);
        static_assert(BLACKDESK_CPPLIB_AND(1, 0) == false);
        static_assert(BLACKDESK_CPPLIB_AND(1, 1) == true);

        static_assert(BLACKDESK_CPPLIB_OR(0, 0) == false);
        static_assert(BLACKDESK_CPPLIB_OR(0, 1) == true);
        static_assert(BLACKDESK_CPPLIB_OR(1, 0) == true);
        static_assert(BLACKDESK_CPPLIB_OR(1, 1) == true);

        static_assert(BLACKDESK_CPPLIB_IF(1, 1, 2) == 1);
        static_assert(BLACKDESK_CPPLIB_IF(0, 1, 2) == 2);

#define DECLARE_EACH(index, contex, arg)                       \
        BLACKDESK_CPPLIB_IF(index, BLACKDESK_CPPLIB_SEMICOLON, \
                            BLACKDESK_CPPLIB_EMPTY)            \
        () contex arg

        BLACKDESK_CPPLIB_FOR_EACH(DECLARE_EACH, int, x, y, z);

        BLACKDESK_CPPLIB_UNUSED(x);
        BLACKDESK_CPPLIB_UNUSED(y);
        BLACKDESK_CPPLIB_UNUSED(z);

#undef DECLARE_EACH

#define SUM_OP(xy_tuple) SUM_OP_OP_IMPL xy_tuple
#define SUM_OP_OP_IMPL(x, y) (BLACKDESK_CPPLIB_DEC(x), y + x)

#define SUM_PRED(xy_tuple) SUM_PRED_IMPL xy_tuple
#define SUM_PRED_IMPL(x, y) x

#define SUM(max_num, origin_num)                                   \
        BLACKDESK_CPPLIB_IDENTITY(SUM_IMPL BLACKDESK_CPPLIB_WHILE( \
                SUM_PRED, SUM_OP, (max_num, origin_num)))
#define SUM_IMPL(ignore, ret) ret

        int a = 1;
        int b = SUM(7, a);
        BLACKDESK_CPPLIB_UNUSED(b);

#undef SUM_OP
#undef SUM_OP_OP_IMPL
#undef SUM_PRED
#undef SUM_PRED_IMPL
#undef SUM
#undef SUM_IMPL

        return 0;
}
