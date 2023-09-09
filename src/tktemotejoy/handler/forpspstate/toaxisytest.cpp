#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/handler/forpspstate/toaxistest.h"
#include "tktemotejoy/pspstate.h"
#include <linux/input.h>

//REMOVEME
namespace {
    struct GenerateToAxisY_old
    {
        auto operator()(
            const __s32     _MIN
            , const __s32   _MAX
            , const __s32   _DEAD_ZONE
            , const __s32   _LIMIT
        ) const
        {
            return ToAxisY_old(
                _MIN
                , _MAX
                , _DEAD_ZONE
                , ToAxisYImpl( _LIMIT )
            );
        }
    };

    using ToAxisY_oldTest = ToAxis_oldTest< GenerateToAxisY_old >;
}

//REMOVEME
TEST_F(
    ToAxisY_oldTest
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
        , 0xc0800000
    );
}
