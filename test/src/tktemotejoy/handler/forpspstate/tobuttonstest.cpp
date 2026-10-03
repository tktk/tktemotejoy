#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"

TEST(
    ToButtonsTest
    , OperatorCall
)
{
    auto    toButtons = ToButtons( 10 );

    auto    pspState = PspState();

    toButtons( pspState );

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
    EXPECT_EQ( 0x8080000a, bits );
}
