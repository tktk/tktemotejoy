#include "tktemotejoy/test.h"
#include "tktemotejoy/handler/forpspstate/tofixedaxisx.h"
#include "tktemotejoy/pspstate.h"

TEST(
    ToFixedAxisXTest
    , OperatorCall
)
{
    auto    toFixedAxisX = tktemotejoy::ToFixedAxisX( 0xc0 );

    auto    pspState = tktemotejoy::PspState();

    toFixedAxisX( pspState );

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
    EXPECT_EQ( 0x80c00000, bits );
}
