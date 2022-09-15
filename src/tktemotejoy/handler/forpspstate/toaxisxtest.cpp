#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/handler/forpspstate/toaxistest.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

namespace {
    //FIXME
    struct GenerateToAxisX
    {
        auto operator()(
            const __s16     _MIN
            , const __s16   _MAX
            , const __s16   _DEAD_ZONE
            , const __s16   _LIMIT
        ) const
        {
            return ToAxisX_new(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToAxisX_newImpl( _LIMIT )
            );
        }
    };

    //FIXME
    using ToAxisX_newTest = ToAxisTest< GenerateToAxisX >;
}

TEST_F(
    ToAxisX_newTest
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
