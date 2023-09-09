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
        ) const
        {
            return ToAxisX_old(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToAxisXImpl_old( _LIMIT )
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
        , 384
        , true
        , 0x80c00000
    );
}
