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
            , const bool            _EXPECTED_CALLED_WHEN_DIFF
            , const PspState::Bits  _EXPECTED_BITS
        ) const
        {
            auto    toAxisY = ToAxisY(
                _DEAD_ZONE
                , ToAxisYImpl( _MAX )
            );

            auto    pspState = PspState();

            toAxisY(
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
    ToAxisYTest
    , Max
)
{
    this->test(
        0
        , 2000
        , 3000
        , true
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
        , false
        , 0
    );
}
