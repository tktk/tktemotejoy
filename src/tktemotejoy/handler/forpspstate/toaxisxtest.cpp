#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/toaxistest.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    struct GenerateToAxisX
    {
        auto operator()(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
            , const __s32   _ERASE_DEAD_ZONE
        ) const
        {
            return ToAxisX(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToAxisXImpl(
                    _LIMIT
                    , _ERASE_DEAD_ZONE
                )
            );
        }
    };

    using ToAxisXTest = ToAxisTest< GenerateToAxisX >;
}

TEST_F(
    ToAxisXTest
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
        , 0x80e00000
    );
}
