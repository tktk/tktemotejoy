#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/toaxisy.h"
#include "tktemotejoy/pspstate.h"
#include <linux/joystick.h>

namespace {
    class ToAxisYTest : public ::testing::Test
    {
    public:
        void test(
            const __s16             _DEAD_ZONE
            , const __s16           _MAX
            , const __s16           _VALUE
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            auto    toAxisY = ToAxisY(
                _DEAD_ZONE
                , _MAX
            );

            auto    pspState = PspState();

            toAxisY(
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
    ToAxisYTest
    , Max
)
{
    this->test(
        0
        , 2000
        , 3000
        , 0xff800000
    );
}

TEST_F(
    ToAxisYTest
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
