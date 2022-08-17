#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    class ToFixedAxisX_operatorCallTest : public ::testing::Test
    {
    public:
        void test(
            const __s16             _AXIS
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            auto    toFixedAxisX = ToFixedAxisX( _AXIS );

            auto    pspState = PspState();

            toFixedAxisX( pspState );

            auto    diffPspState = PspState();
            diffPspState.pressButtons( 10 );

            pspState.diff(
                diffPspState
                , [
                    &_EXPECTED_BITS
                ]
                (
                    const PspState::Bits &  _BITS
                )
                {
                    EXPECT_EQ( _EXPECTED_BITS, _BITS );
                }
            );
        }
    };
}

TEST_F(
    ToFixedAxisX_operatorCallTest
    , Max
)
{
    this->test(
        32767
        , 0x00ff0000
    );
}

//TODO Zero
//TODO Min
