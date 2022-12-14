#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/pspstate.h"

TEST(
    ToFixedAxisYTest
    , OperatorCall
)
{
    auto    toFixedAxisY = ToFixedAxisY( 0xc0 );

    auto    pspState = PspState();

    toFixedAxisY( pspState );

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

    EXPECT_TRUE( calledWhenDiff );
    EXPECT_EQ( 0xc0800000, bits );
}
