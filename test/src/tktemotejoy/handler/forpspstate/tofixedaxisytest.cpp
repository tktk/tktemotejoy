#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisy.h"
#include "tktemotejoy/pspstate.h"

TEST(
    ToFixedAxisYTest
    , OperatorCall
)
{
    auto    toFixedAxisY = tktemotejoy::ToFixedAxisY( 0xc0 );

    auto    pspState = tktemotejoy::PspState();

    toFixedAxisY( pspState );

    const auto  OTHER = tktemotejoy::PspState();

    auto    calledWhenDiff = false;
    auto    bits = tktemotejoy::PspState::Bits();

    pspState.runWhenDiff(
        OTHER
        , [
            &calledWhenDiff
            , &bits
        ]
        (
            const tktemotejoy::PspState::Bits & _BITS
        )
        {
            calledWhenDiff = true;
            bits = _BITS;
        }
    );

    EXPECT_TRUE( calledWhenDiff );
    EXPECT_EQ( 0xc0800000, bits );
}
