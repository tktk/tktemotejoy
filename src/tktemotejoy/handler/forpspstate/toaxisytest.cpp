#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/toaxistest.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    struct GenerateToAxisY
    {
        auto operator()(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
            , const __s32   _ERASE_DEAD_ZONE
        ) const
        {
            return ToAxisY(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToAxisYImpl(
                    _LIMIT
                    , _ERASE_DEAD_ZONE
                )
            );
        }
    };

    using ToAxisYTest = ToAxisTest< GenerateToAxisY >;
}

TEST_F(
    ToAxisYTest
    , Standard
)
{
    this->test(
        0
        , 511
        , 10
        , 256
        , 64
        , 384
        , true
        , 0xe0800000
    );
}
