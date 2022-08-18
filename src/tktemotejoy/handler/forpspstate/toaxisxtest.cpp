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
            , const bool            _EXPECTED_CALLED_WHEN_DIFF
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

            const auto  OTHER = PspState();

            auto    calledWhenDiff = false;
            auto    bits = PspState::Bits();

            pspState.diff(
                OTHER
                , [
                    &calledWhenDiff
                    , &bits
                ]
                (
                    const PspState::Bits &  _BITS
                )
                {
                    calledWhenDiff = true;
                    bits = _BITS;
                }
            );

            EXPECT_EQ( _EXPECTED_CALLED_WHEN_DIFF, calledWhenDiff );

            if( calledWhenDiff == true ) {
                EXPECT_EQ( _EXPECTED_BITS, bits );
            }
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
        , true
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
        , false
        , 0
    );
}
