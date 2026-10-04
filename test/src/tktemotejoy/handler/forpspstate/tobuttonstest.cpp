#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tobuttons.h"

TEST(
    ToButtonsTest
    , OperatorCall
)
{
    auto    toButtons = tktemotejoy::ToButtons( 10 );

    auto    pspState = tktemotejoy::PspState();

    toButtons( pspState );

    const auto  OTHER = tktemotejoy::PspState();

    auto    calledWhenDiff = false;
    auto    bits = tktemotejoy::PspState::Bits();

    pspState.diff(
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
    EXPECT_EQ( 0x8080000a, bits );
}
