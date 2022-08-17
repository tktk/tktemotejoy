#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/toaxisx.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    class ToAxisXTest : public ::testing::Test
    {
    public:
        void test(
            const __s16             _DEAD_ZONE
            , const __s16           _MAX
            , const __s16           _VALUE
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            auto    toAxisX = ToAxisX(
                _DEAD_ZONE
                , ToAxisXImpl( _MAX )
            );

            auto    pspState = PspState();

            toAxisX(
                _VALUE
                , pspState
            );

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
    ToAxisXTest
    , Max
)
{
    this->test(
        0
        , 2000
        , 3000
        , 0x80ff0000
    );
}

TEST_F(
    ToAxisXTest
    , DeadZone
)
{
    this->test(
        1000
        , 2000
        , 500
        , 0x80800000
    );
}
